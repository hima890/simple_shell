<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid, wpid;
    int status;

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0)
    {
        // This is the child process
        printf("Child process is running\n");
        exit(0); // Terminate the child process
    }
    else
    {
        // This is the parent process
        printf("Parent process is waiting for the child to finish...\n");
        wpid = wait(&status);

        if (wpid == -1)
        {
            perror("wait");
            exit(1);
        }

        if (WIFEXITED(status))
        {
            printf("Child process with PID %d exited with status %d\n", wpid, WEXITSTATUS(status));
        }
    }

    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid, wpid;
    int status;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // This is the child process
        printf("Child process is running\n");
        exit(0); // Terminate the child process
    } else {
        // This is the parent process
        printf("Parent process is waiting for the child to finish...\n");
        wpid = wait(&status);

        if (wpid == -1) {
            perror("wait");
            exit(1);
        }

        if (WIFEXITED(status)) {
            printf("Child process with PID %d exited with status %d\n", wpid, WEXITSTATUS(status));
        }
    }

    return 0;
}
>>>>>>> 1874d354ae5ad4d31b24c93a3b0a71b6bf32d14b
