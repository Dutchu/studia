#include <windows.h>
#include <stdio.h>
#include <sehmap.h>
#include <atomic>
#include <iostream>

struct resource {    /* Used as argument to th_routine() */
    DWORD lastThreadId;        /* Last thread ID to edit resources */
    ssize_t lastThreadNum;             /* Last thread # to edit resources */
    ssize_t order;                      /* order in which threads are to be executed */
    char *data;                     /* Place to note thread entry order */
};

struct thread_args {
    DWORD threadId;
    ssize_t threadNum;
    HANDLE hThread;
    struct resource *commonResource;
};

std::atomic<int> threadToExecute = {0}; /* Thread execution order tool */
HANDLE hMutex; /* Thread locking mechanism */

DWORD WINAPI threadMainRoutine(LPVOID lpParam);
int createThreadInc(int threadCount, thread_args* aThreads, resource* singleResource, HANDLE* aThreadsID);
int createThreadDec(int threadCount, thread_args* aThreads, resource* singleResource, HANDLE* aThreadsID);

static void critical_section(struct thread_args *);

int main(int argc, char** argv) {
    int threadCount, order;
    auto *singleResource = new resource[1]{0};
    singleResource->data = new char[threadCount * 4 + 1]{0};
    thread_args *aThreads; //structure with thread information and a pointer to memory shared by all threads
    HANDLE *aThreadsID; //handles array for Windows thread manipulation

    if (argc != 3) {
        fprintf(stderr, "%s : Incorrect number of program arguments given!\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *end_ptr = nullptr;
    threadCount = strtol(argv[1], &end_ptr, 10);
    if (threadCount == 0) {
        fprintf(stderr, "%s : Incorrect number of aThreads given!\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    aThreads = new thread_args[threadCount];
    aThreadsID = new HANDLE[threadCount];
    switch (*argv[2]) {
        case 'd':
            order = 0;
            break;
        case 'i':
            order = 1;
            break;
        default:
            order = -1;
    }
    if (order == -1) {
        fprintf(stderr, "%s : Incorrect second option!\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    singleResource->order = order;


    // Create a mutex with no initial owner
    hMutex = CreateMutex(
            NULL,              // default security attributes
            FALSE,             // initially not owned
            NULL);             // unnamed mutex

    if (hMutex == NULL) {
        printf("CreateMutex error: %d\n", GetLastError());
        return 1;
    }

    // Create worker threads
    std::cout << "Execution order (inc - 1, desc - 0): " << order << ", thread count: " << threadCount << std::endl;
    switch (order) {
        case 0:
            createThreadDec(threadCount, aThreads, singleResource, aThreadsID);
            threadToExecute.store(threadCount - 1);
            break;
        case 1:
            createThreadInc(threadCount, aThreads, singleResource, aThreadsID);
            break;
        default:
            return FALSE;
    }


    // Wait for all threads to terminate
    WaitForMultipleObjects(threadCount, aThreadsID, TRUE, INFINITE);

    // Close thread and mutex handles
    for (int i = 0; i < threadCount; i++)
        CloseHandle(aThreadsID[i]);

    CloseHandle(hMutex);
    free(singleResource->data);
    free(singleResource);
    free(aThreads);

    return 0;
}

DWORD WINAPI threadMainRoutine(LPVOID lpParam) {

    auto *args = (struct thread_args *) lpParam;
    DWORD dwWaitResult;

    printf("Current atomic value: %d for Thread %ld\n", threadToExecute.load(), args->threadNum);
    while (threadToExecute.load() != args->threadNum) {
        printf("Thread %ld waiting... Current atomic value: %d\n", args->threadNum, threadToExecute.load());
        Sleep(1000);
    }

    dwWaitResult = WaitForSingleObject(
            hMutex,    // handle to mutex
            INFINITE);  // no time-out interval

    switch (dwWaitResult) {
        // The thread got ownership of the mutex
        case WAIT_OBJECT_0:
            printf("Thread %d writing to database...\n",
                   GetCurrentThreadId());
            critical_section(args);

            switch (args->commonResource->order) {
                case 0:
                    threadToExecute.fetch_sub(1);
                    break;
                case 1:
                    threadToExecute.fetch_add(1);
                    break;
                default:
                    return FALSE;
            }
            // Release ownership of the mutex object
            ReleaseMutex(hMutex);
        case WAIT_ABANDONED:
            return FALSE;
    }
    return TRUE;
}

static void critical_section(struct thread_args *th_info) {
    char *comm_data;
    int s = 0;
    printf("Thread %ld: working...\n", th_info->threadNum);

    printf("Last thread to edit: Thread %ld, id = ", th_info->commonResource->lastThreadNum);
    printf("%ld\n", th_info->commonResource->lastThreadId);

    comm_data = (th_info->commonResource->data);
    printf("Thread %ld: id = %ld in critical_section() : ", th_info->threadNum, th_info->threadId);
    printf("Resource address: %p\n", th_info->commonResource);

    int length = snprintf(NULL, 0, "%ld", th_info->threadNum);
    char *th_data = static_cast<char *>(malloc(length + 1));
    s = snprintf(th_data, length + 1, "%ld", th_info->threadNum);
    if (s < 0) {
        fprintf(stderr, "th_routine() failed - couldn't note data with snprintf()");
        exit(EXIT_FAILURE);
    }

    strcat(comm_data, th_data);
    strcat(comm_data, "->");

    printf("%s\n", comm_data);

    th_info->commonResource->lastThreadId = th_info->threadId;
    th_info->commonResource->lastThreadNum = th_info->threadNum;

    free(th_data);

    Sleep(1000);
}

int createThreadInc(int threadCount, thread_args* aThreads, resource* singleResource, HANDLE* aThreadsID) {
    for (int i = 0; i < threadCount; i++) {
        aThreads[i].hThread = CreateThread(
                NULL,       // default security attributes
                0,          // default stack size
                (LPTHREAD_START_ROUTINE) threadMainRoutine,
                &aThreads[i],       // no thread function arguments
                CREATE_SUSPENDED,          // default creation flags
                &aThreads[i].threadId); // receive thread identifier

        if (aThreads[i].hThread == NULL) {
            fprintf(stderr, "CreateThread error: %d\n", GetLastError());
            return 1;
        }

        // Pass thread number
        aThreads[i].threadNum = i;
        aThreads[i].commonResource = singleResource;

        // Run the thread
        if (ResumeThread(aThreads[i].hThread) == -1) {
            fprintf(stderr, "th_routine() failed - couldn't note data with snprintf() %d", GetLastError());
            return -1;
        }

        //give threads handle to the array of handles for further manipulation requiring such data structure
        aThreadsID[i] = aThreads[i].hThread;
    }
}

int createThreadDec(int threadCount, thread_args* aThreads, resource* singleResource, HANDLE* aThreadsID) {
    for (int i = threadCount - 1; i >= 0; i--) {
        aThreads[i].hThread = CreateThread(
                NULL,       // default security attributes
                0,          // default stack size
                (LPTHREAD_START_ROUTINE) threadMainRoutine,
                &aThreads[i],       // no thread function arguments
                CREATE_SUSPENDED,          // default creation flags
                &aThreads[i].threadId); // receive thread identifier

        if (aThreads[i].hThread == NULL) {
            fprintf(stderr, "CreateThread error: %d\n", GetLastError());
            return 1;
        }

        // Pass thread number
        aThreads[i].threadNum = i;
        aThreads[i].commonResource = singleResource;

        // Run the thread
        if (ResumeThread(aThreads[i].hThread) == -1) {
            fprintf(stderr, "th_routine() failed - couldn't note data with snprintf() %d", GetLastError());
            return -1;
        }

        //give threads handle to the array of handles for further manipulation requiring such data structure
        aThreadsID[i] = aThreads[i].hThread;
    }
}