#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define SIZESTACK (1020 * 1020)

int c_create_child(void *arg)
{
    printf("New process - My PID: %d\n", getpid());
    printf("Child process arg = %s\n", (char *)arg);
    // printf("[%s] is argv ?.\n", (char *)arg);
    return 0;
}

int f_create_child(int argc, char **argv)
{
    int status;
    int forkpid;
    printf("\n[%s] is argv %d.\n", argv[0], 0);
    printf("My PID: %d\n", getpid());
    for (int i = 1; i < argc; i++)
    {

        forkpid = fork();
        if (forkpid == 0)
        {
            printf("\n[%s] is argv %d.\n", argv[i], i);
            printf("My PID: %d\n", getpid());
            return 0;
        }

        waitpid(forkpid, &status, 0);
    }
}

int main(int argc, char *argv[])
{

    char *stack;
    char *stackhead;
    char *str = "Hello, World!\n";

    pid_t pid;
    int status;

    stack = (char *)malloc(SIZESTACK);

    if (!stack)
    {
        fprintf(stderr, "Unable to allocate stack.\n");
        exit(1);
    }

    stackhead = stack + SIZESTACK - 1;

    printf("\nNumber of arguments passed to program = %d\n", argc);
    printf("main() - My PID: %d\n", getpid());

    if (argc == 1)
    {
        printf("\n[%s] No arguments passed to program.\n", argv[0]);
        return 0;
    }

    if (**(argv + 1) == 'c')
    {

        for (int i = 1; i < argc; i++)
        {
            pid = clone(c_create_child, stackhead, SIGCHLD, *(argv + i));

            if (pid == -1)
            {
                fprintf(stderr, "Unable to clone.\n");
                free(stack);
                exit(1);
            }
            waitpid(pid, &status, 0);
        }
    }
    else
    {
        f_create_child(argc, argv);
    }

    return 0;
}