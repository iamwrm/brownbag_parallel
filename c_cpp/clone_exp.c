
#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#define STACK_SIZE (1024 * 1024) /* Stack size for cloned child */

#define errExit(msg)        \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

static int childFunc(void *counter)
{
    *(int *)counter += 233;
    return 0;
}

int main(int argc, char *argv[])
{
    char *stack;
    char *stackTop;
    stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
    if (stack == MAP_FAILED)
        errExit("mmap");
    stackTop = stack + STACK_SIZE;
    int *counter_ptr = malloc(1 * sizeof(int));

    // ===============================================================================
    *counter_ptr = 0;
    printf("In main process, counter %d\n", *counter_ptr);

    // pid_t pid = clone(childFunc, stackTop, SIGCHLD, (void *)counter_ptr);
    pid_t pid = clone(childFunc, stackTop, SIGCHLD | CLONE_VM, (void *)counter_ptr);
    if (pid == -1)
        errExit("clone");
    if (waitpid(pid, NULL, 0) == -1) /* Wait for child */
        errExit("waitpid");

    printf("In main process, counter %d\n", *counter_ptr);

    // ===============================================================================
    free(counter_ptr);
    exit(EXIT_SUCCESS);
}