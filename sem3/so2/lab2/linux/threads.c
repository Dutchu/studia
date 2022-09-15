#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
               do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct resource {    /* Used as argument to th_routine() */
    pthread_t last_thread_id;        /* Last thread ID to edit resources */
    ssize_t last_thread_num;             /* Last thread # to edit resources */
    ssize_t order;                      /* order in which threads are to be executed */
    char *data;                     /* Place to note thread entry order */
    _Atomic int current_in_service; /* Thread-safe thread entry order tool */
};


struct thread_info {                     /* Used as argument to th_routine() */
    pthread_t thread_id;                 /* ID returned by pthread_create() */
    ssize_t thread_num;                      /* Application-defined thread # */
    struct resource *common_resource;    /* Resource */
};

void create_process_inc(long threads_num, struct resource *single_resource, struct thread_info *th_info);

void create_process_dec(long threads_num, struct resource *single_resource, struct thread_info *th_info);

static void critical_section(struct thread_info* th_info);

static void *th_routine(void *arg);

pthread_mutex_t mutex;
/***
 * Program function:
 * Edit single point in memory with different threads in ordered manner.
 * Program usage:
 * In console provide flag -i or -d to declare in which order threads will access single point of memory to edit.
 * as second argument provide number of threads that are supposed to be created.
 */
int main(int argc, char **argv) {
    int s, opt;
    long threads_num;
    ssize_t order;
    void *res;
    pthread_mutex_init(&mutex, NULL);
    struct resource *single_resource = calloc(sizeof(struct resource), 1);

    for (int i = 1; i < argc; ++i) {
        printf("argv %d: %s\n", i, argv[i]);
    }
    printf("argc: %d\n", argc);

    /***
    * Parse arguments of program.
    */
    if (argc > 3) {
        fprintf(stderr, "%s: Wrong program arguments count!\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /***
     * The "-i" or "-d" flags specifies in which order execute threads; Incremental or Decremental
     * */
    order = -1;
    while ((opt = getopt(argc, argv, "id")) != -1) {
        switch (opt) {
            case 'i':
                order = 1;
                break;
            case 'd':
                order = 0;
                break;

            default:
                fprintf(stderr, "%s: [-s stack-size] arg...\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    printf("order: %ld\n", order);
    single_resource->order = order;

    /***
     * Acquire threads number
     */
    char *end_ptr = NULL;
    threads_num = strtol(argv[2], &end_ptr, 10);
    if (threads_num == 0) {
        fprintf(stderr, "%s : Wrong second argument type. Could not use strtol()!\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /***
    * Allocate heap for single source of data for threads
    */

    if (single_resource == NULL)
        handle_error("calloc");
    printf("Program resource address: %p\n", single_resource);


    /***
    *  Allocate heap for data to modify by threads (4 bytes for thread number, 2 bytes for "->", 1 byte for '\0')
    */
    single_resource->data = calloc(sizeof(char), sizeof(int) * threads_num * 2 + 1);
    if (single_resource->data == NULL)
        handle_error("calloc");

    /***
    * Allocate heap for structure holding threads information
    */
    struct thread_info *th_info = calloc(threads_num, sizeof(*th_info));
    if (th_info == NULL)
        handle_error("calloc");

    /***
     * Create one thread for each command-line argument.
     */

    switch (order) {
        case 0:
            create_process_dec(threads_num, single_resource, th_info);
            single_resource->current_in_service = threads_num - 1;
            break;
        case 1:
            create_process_inc(threads_num, single_resource, th_info);
            single_resource->current_in_service = 1;
            break;
        default:
            fprintf(stderr, "%s: variable (int) order not 0 nor 1!\n", argv[0]);
            exit(EXIT_FAILURE);
    }


    /***
     * Now join with each thread, and display its returned value.
     */
    for (int th_num = 0; th_num < threads_num; th_num++) {
        s = pthread_join(th_info[th_num].thread_id, &res);
        if (s != 0)
            handle_error_en(s, "pthread_join");

        printf("Main joined with thread %ld; returned value was %s\n",
               th_info[th_num].thread_num, (char *) res);
    }

    pthread_mutex_destroy(&mutex);
    free(single_resource->data);
    free(single_resource);
    free(th_info);
    exit(EXIT_SUCCESS);
}

void create_process_inc(long threads_num, struct resource *single_resource, struct thread_info *th_info) {
    int s;
    for (int th_num = 0; th_num < threads_num; th_num++) {
        th_info[th_num].thread_num = th_num + 1;
        th_info[th_num].common_resource = single_resource;

        /***
         * The pthread_create() call stores the thread ID into corresponding element of tinfo[].
         */
        s = pthread_create(&th_info[th_num].thread_id, NULL,
                           &th_routine, &th_info[th_num]);
        if (s != 0)
            handle_error_en(s, "pthread_create");
    }
}

void create_process_dec(long threads_num, struct resource *single_resource, struct thread_info *th_info) {
    int s;
    for (ssize_t th_num = (threads_num - 1); th_num >= 0; th_num--) {
        th_info[th_num].thread_num = th_num;
        th_info[th_num].common_resource = single_resource;

        /***
         * The pthread_create() call stores the thread ID into corresponding element of tinfo[].
         */
        s = pthread_create(&th_info[th_num].thread_id, NULL,
                           &th_routine, &th_info[th_num]);
        if (s != 0)
            handle_error_en(s, "pthread_create");

    }
}


static void *th_routine(void *arg) {

    if (arg == NULL) {
        fprintf(stderr, "th_routine() failed - null arguments");
        return "FAILURE";
    }
    struct thread_info *th_info = arg;

    printf("%d",th_info->common_resource->current_in_service);
    printf("%ld",th_info->thread_num);


    printf("Thread %ld waiting for mutex!\n", th_info->thread_num);
    while (th_info->common_resource->current_in_service != th_info->thread_num) {
        sleep(1);
        printf("Thread %ld waiting...\n", th_info->thread_num);
    }
    switch (th_info->common_resource->order) {
        case 1:
            th_info->common_resource->current_in_service ++;
            break;
        case 0:
            th_info->common_resource->current_in_service --;
            break;
        default:
            fprintf(stderr, "%ld: Thread failed! \n", th_info->thread_id);
            exit(EXIT_FAILURE);
    }

    pthread_mutex_lock(&mutex);
    critical_section(th_info);
    pthread_mutex_unlock(&mutex);
    return "SUCCESS";
}

static void critical_section(struct thread_info* th_info) {
    char *comm_data;
    int s = 0;
    printf("Thread %ld: working...\n", th_info->thread_num);

    printf("Last thread to edit: Thread %ld, id = ", th_info->common_resource->last_thread_num);
    printf("%ld\n", th_info->common_resource->last_thread_id);

    comm_data = (th_info->common_resource->data);
    printf("Thread %ld: id = %ld\n", th_info->thread_num, th_info->thread_id);
    printf("Resource address: %p\n", th_info->common_resource);

    int length = snprintf(NULL, 0, "%ld", th_info->thread_num);
    char *th_data = malloc(length + 1);
    s = snprintf(th_data, length + 1, "%ld", th_info->thread_num);
    if (s < 0) {
        fprintf(stderr, "th_routine() failed - couldn't note data with snprintf()");
        exit(EXIT_FAILURE);
    }

    strcat(comm_data, th_data);
    strcat(comm_data, "->");

    printf("%s\n", comm_data);

    th_info->common_resource->last_thread_id = th_info->thread_id;
    th_info->common_resource->last_thread_num = th_info->thread_num;

    free(th_data);

    sleep(1);
}