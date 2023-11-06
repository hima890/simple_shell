#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t my_ppid;
    long max_value;

    my_ppid = getppid();
    my_pid = getpid();
    max_value = sysconf(_SC_CHILD_MAX);
    printf("PID: %u\n", my_pid);
    printf("PPID: %u\n", my_ppid);
    printf("MAX PID: %ld\n", max_value);

    return (0);
}