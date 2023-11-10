#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

#define MAX_ARGS 100

int command_exists(char *cmd_name) {
    return access(cmd_name, X_OK) == 0;
}

int main(int argc, char * const argv[], char **env) {
    while (1) {
        char *line_buffer = NULL;
        size_t line_buffer_size = 0;
        ssize_t read;
        
        // Check if the standard input is a terminal
        int is_interactive = isatty(STDIN_FILENO);


        if (is_interactive)
        {
            // Print the prompt only if in interactive mode and it's not an exit command
            printf("$ ");
        }

        if ((read = getline(&line_buffer, &line_buffer_size, stdin)) == -1) {
            if (feof(stdin)) {
                // End of input reached, break out of the loop
                free(line_buffer);
                break;
            } else {
                perror(argv[0]);
                free(line_buffer);
                continue;
            }
        }
        
        // Remove the newline character from the buffer if it exists
        if ((read > 0) && (line_buffer[read - 1] == '\n')) {
            line_buffer[read - 1] = '\0';
        }
        
        int argc = 0;
        char *cmd_argv[MAX_ARGS];
        
        // Tokenize the input line
        char *token = strtok(line_buffer, " ");
        while (token != NULL && argc < MAX_ARGS) {
            if (strcmp(token, "") != 0) {
                cmd_argv[argc] = token;
                argc++;
            }
            token = strtok(NULL, " ");
        }
        cmd_argv[argc] = NULL; // Null-terminate the argument array
        
        if (argc == 0) {
            // No command provided, continue to the next iteration
            free(line_buffer);
            continue;
        }

        // Handle the "exit" command
        if (strcmp(cmd_argv[0], "exit") == 0) {
            int exit_status = 0;
            if (cmd_argv[1] != NULL) {
                exit_status = atoi(cmd_argv[1]);
            }
            free(line_buffer);
            exit(exit_status);
        }
        
        // Handle the "env" command
        if (strcmp(cmd_argv[0], "env") == 0) {
            unsigned int i;

            i = 0;
            while (env[i] != NULL)
            {
                printf("%s\n", env[i]);
                i++;
            }
            free(line_buffer);
            continue;
        }

        // Check if the specified command exists at the provided path
        char *cmd_name = cmd_argv[0];
        char absolute_path[PATH_MAX];

        if (command_exists(cmd_name)) {
            // The user entered an absolute or relative path to the command
            strncpy(absolute_path, cmd_name, PATH_MAX);
        } else {
            // Search for the command path in directories listed in PATH
            char *path = getenv("PATH");
            if (path == NULL) {
                perror(argv[0]);
                free(line_buffer);
                continue;
            }

            char *path_copy = strdup(path);
            int command_found_flag = 0;
            
            const char *delim_2 = ":";
            char *path_token = strtok(path_copy, delim_2);
            
            while (path_token != NULL) {
                DIR *command_dir = opendir(path_token);
                if (command_dir) {
                    struct dirent *ent;
                    while ((ent = readdir(command_dir)) != NULL) {
                        if (ent->d_type == DT_REG && strcmp(ent->d_name, cmd_name) == 0) {
                            snprintf(absolute_path, PATH_MAX, "%s/%s", path_token, ent->d_name);
                            command_found_flag = 1;
                            break;
                        }
                    }
                    closedir(command_dir);
                } else {
                    perror(argv[0]);
                }
                
                path_token = strtok(NULL, delim_2);
                
                if (command_found_flag == 1) {
                    break;
                }
            }
            
            free(path_copy);
            
            if (command_found_flag == 0) {
                fprintf(stderr, "%s: %d: %s: not found\n", argv[0], __LINE__, cmd_name);
                free(line_buffer);
                continue;
            }
        }
        
        // Create a child process and execute the command
        pid_t fork_processor, wpid;
        int status;
        
        fork_processor = fork();
        
        if (fork_processor == -1) {
            perror(argv[0]);
            free(line_buffer);
            continue;
        }
        
        if (fork_processor == 0) {
            if (execve(absolute_path, cmd_argv, NULL) == -1) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        } else {
            wpid = wait(&status);
            if (wpid == -1) {
                perror(argv[0]);
            }
        }

        free(line_buffer);
    }
    
    return 0;
}
