#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    pid_t child_pid, wpid;
    int status;
    int count = 5;

    

    

    for (size_t i = 0; i < count; i++)
    {
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
        } else
        {
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



    }
    
    return 0;
}
