#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
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

        if (strcmp(line_buffer, "q") == 0)
        {
            free(line_buffer);
            exit(0);
        }
        else
        {
            // Tokenize the input line and execute the command
            char *token = strtok(line_buffer, " ");
            int argc = 0;
            char *cmd_argv[20]; // Adjust the size as needed

            while (token != NULL)
            {
                if (argc < 20)
                {
                    cmd_argv[argc] = token;
                    argc++;
                    token = strtok(NULL, " ");
                }
                else
                {
                    fprintf(stderr, "Too many arguments, ignoring the rest.\n");
                    break;
                }
            }
            cmd_argv[argc] = NULL; // Null-terminate the argument array

            char *path = getenv("PATH");
            if (path == NULL)
            {
                perror("PATH environment variable not found.");
            }
            else
            {
                printf("PATH environment variable found.\n");
                const char *delim_2 = ":";
                char *token_2 = strtok(path, delim_2);
                char full_path[512]; // Adjust the size as needed

                while (token_2 != NULL)
                {
                    
                    DIR *dir = opendir(token_2);
                    if (dir)
                    {
                        struct dirent *ent;
                        while ((ent = readdir(dir)) != NULL)
                        {
                            if (ent->d_type == DT_REG)
                            {
                                for (int i = 0; i < argc; i++)
                                {
                                    if (strcmp(ent->d_name, cmd_argv[i]) == 0)
                                    {
                                        snprintf(full_path, sizeof(full_path), "%s/%s", token_2, cmd_argv[i]);
                                        printf("Executing: %s\n", full_path);
                                        // execvp(full_path, cmd_argv);
                                        // perror("Execution failed");
                                        // If execvp failed, you can handle the error here.
                                        // The code after this point will only execute if execvp fails.
                                        

                                    }
                                }
                            }
                        }
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
                            execvp(full_path, cmd_argv);
                            free(line_buffer);
                            // execve(full_path, argv, NULL);
                            perror("Execution failed");
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
                        
                        closedir(dir);
                    }
                    else
                    {
                        printf("Could not open directory.");
                    }
                    token_2 = strtok(NULL, delim_2);
                }
                printf("Command not found in any directory.\n");
            }
        }
    }

    free(line_buffer);
    return 0;
}


