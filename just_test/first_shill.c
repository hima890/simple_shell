#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * const argv[]) {
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    ssize_t read;

    while (1) {
        printf("$ ");
        read = getline(&line_buffer, &line_buffer_size, stdin);

        if (read == -1) {
            perror("Read the line!");
            break;
        }

        line_buffer[read - 1] = '\0';  // Remove the newline character

        if (strcmp(line_buffer, "q") == 0) {
            free(line_buffer);
            exit(0);
        } else {
            // Tokenize the input line and execute the command
            char *token = strtok(line_buffer, " ");
            int argc = 0;
            char *cmd_argv[20]; // Adjust the size as needed
            
            while (token != NULL) {
                if (argc < 20) {
                    cmd_argv[argc] = token;
                    argc++;
                    token = strtok(NULL, " ");
                } else {
                    fprintf(stderr, "Too many arguments, ignoring the rest.\n");
                    break;
                }
            }
            cmd_argv[argc] = NULL; // Null-terminate the argument array
            
            pid_t child_pid, wpid;
            int status;

            child_pid = fork();

            if (child_pid == -1) {
                perror("fork");
                exit(1);
            }

            if (child_pid == 0) {
                // This is the child process
                execve(cmd_argv[0], cmd_argv, NULL);
                free(line_buffer);
                perror("Error executing command!");
                exit(1); // Terminate the child process
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
        }
    }

    free(line_buffer);
    return 0;
}
