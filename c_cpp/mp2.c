#define _GNU_SOURCE


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <sched.h>
#include <linux/sched.h>

#define ITER_TIME 5

void *new_thread_func(void *counter_ptr)
{
    for (int i = 0; i < ITER_TIME; ++i)
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
    char stack[20]; 

    pid_t pid = clone(new_thread_func, stack+4, CLONE_VM, counter_ptr);
    // pid_t pid = fork();

    // printf("%d",pid);
    for (int i = 0; i < ITER_TIME; ++i)
    {
        pid_t curr_pid = getpid();
        printf("child process pid=%d, counter=%d\n", curr_pid, ++(*counter_ptr));
    }

    return 0;
}