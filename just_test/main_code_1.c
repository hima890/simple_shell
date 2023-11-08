#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char * const argv[]) {
    while (1) {
        char *line_buffer = NULL;
        size_t line_buffer_size = 0;
        ssize_t read;

        printf("$ ");
        read = getline(&line_buffer, &line_buffer_size, stdin);

        if (read == -1) {
            perror("Error reading input");
            free(line_buffer);
            exit(-1);
        }

        line_buffer[read - 1] = '\0';  /* Remove the newline character from the buffer */

        char *token = strtok(line_buffer, " ");
        int argc = 0;
        char *cmd_argv[100];

        while (token != NULL && argc < 100) {
            if (strcmp(token, "") != 0) {
                cmd_argv[argc] = token;
                argc++;
            }
            token = strtok(NULL, " ");
        }
        cmd_argv[argc] = NULL;

        if (argc == 0) {
            free(line_buffer);
            continue;  // Empty command, continue to the next iteration
        }

        if (strcmp(cmd_argv[0], "exit") == 0) {
            if (cmd_argv[1] == NULL) {
                free(line_buffer);
                exit(0);
            }
            int exit_status = atoi(cmd_argv[1]);
            free(line_buffer);
            exit(exit_status);
        }

        if (strcmp(cmd_argv[0], "env") == 0) {
            extern char **environ;
            int i = 0;
            for (i = 0; environ[i] != NULL; i++) {
                printf("%s\n", environ[i]);
            }
            free(line_buffer);
            continue;  // Continue to the next iteration
        }

        char *path = getenv("PATH");

        if (path == NULL) {
            perror("The PATH variable is empty");
            free(line_buffer);
            exit(-1);
        }

        char *path_copy = strdup(path);
        char *path_token = strtok(path_copy, ":");
        char absolute_path[PATH_MAX];

        while (path_token != NULL) {
            DIR *command_dir = opendir(path_token);

            if (command_dir) {
                struct dirent *ent;

                while ((ent = readdir(command_dir)) != NULL) {
                    if (ent->d_type == DT_REG && strcmp(ent->d_name, cmd_argv[0]) == 0) {
                        snprintf(absolute_path, PATH_MAX, "%s/%s", path_token, ent->d_name);
                        pid_t fork_processer = fork();

                        if (fork_processer == -1) {
                            perror("Forking failed");
                            exit(-1);
                        }

                        if (fork_processer == 0) {
                            if (execve(absolute_path, cmd_argv, NULL) == -1) {
                                perror("Execve error");
                                exit(-1);
                            }

                            exit(0);
                        } else {
                            int status;
                            pid_t wpid = wait(&status);

                            if (wpid == -1) {
                                perror("Wait error");
                                exit(-1);
                            }
                        }
                    }
                }

                closedir(command_dir);
            } else {
                perror("Could not open the command directory");
            }

            path_token = strtok(NULL, ":");
        }

        free(path_copy);
        printf("%s: command not found\n", cmd_argv[0]);
        free(line_buffer);
    }
    
    return 0;
}
