#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define ITERTIME 5

void *new_thread_func(void *counter_ptr)
{
    for (int i = 0; i < ITERTIME; ++i)
    {
        pid_t pid = getpid();
        printf("new thread pid=%d, counter=%d\n", pid, ++(*((int *)counter_ptr)));
        // ++(*((int *)counter_ptr));
    }
    return 0;
}

int main()
{
    int counter = 0;
    int *counter_ptr = &counter;

    pthread_t tid;

    pthread_create(&tid, NULL, new_thread_func, counter_ptr);

    pid_t pid = getpid();

    // parent process
    for (int j = 0; j < ITERTIME; ++j)
    {
        printf("main thread pid=%d, counter=%d\n", pid, ++(*counter_ptr));
        // ++(*((int *)counter_ptr));
    }

    pthread_join(tid, NULL);

    return 0;
}