#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define ITER_TIME 5

int main()
{
    int counter = 0;
    int *counter_ptr = &counter;

    pid_t pid = fork();

    if (pid == 0)
    {
        // child process
        for (int i = 0; i < ITER_TIME; ++i)
        {
            pid_t curr_pid = getpid();
            printf("child process pid=%d, counter=%d\n", curr_pid, ++(*counter_ptr));
        }
    }
    else if (pid > 0)
    {
        // parent process
        for (int j = 0; j < ITER_TIME; ++j)
        {
            pid_t curr_pid = getpid();
            printf("parent process pid=%d, counter=%d\n", curr_pid, ++(*counter_ptr));
        }
    }

    return 0;
}