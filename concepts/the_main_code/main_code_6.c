#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

#define MAX_ARGS 100

int main(int argc, char * const argv[])
{
    while (1)
    {
        char *line_buffer = NULL;
        size_t line_buffer_size = 0;
        ssize_t read;
        printf("$ ");
        
        if ((read = getline(&line_buffer, &line_buffer_size, stdin)) == -1)
        {
            perror(argv[0]);
            free(line_buffer);
            continue;
        }
        
        // Remove the newline character from the buffer
        line_buffer[read - 1] = '\0';
        
        int argc = 0;
        char *cmd_argv[MAX_ARGS];
        
        // Tokenize the input line
        char *token = strtok(line_buffer, " ");
        while (token != NULL && argc < MAX_ARGS)
        {
            if (strcmp(token, "") != 0)
            {
                cmd_argv[argc] = token;
                argc++;
            }
            token = strtok(NULL, " ");
        }
        cmd_argv[argc] = NULL; // Null-terminate the argument array
        
        if (argc == 0)
        {
            // No command provided, continue to the next iteration
            free(line_buffer);
            continue;
        }

        // Handle the "exit" command
        if (strcmp(cmd_argv[0], "exit") == 0)
        {
            int exit_status = 0;
            if (cmd_argv[1] != NULL)
            {
                exit_status = atoi(cmd_argv[1]);
            }
            free(line_buffer);
            exit(exit_status);
        }
        
        // Handle the "env" command
        if (strcmp(cmd_argv[0], "env") == 0)
        {
            extern char **environ;
            for (int i = 0; environ[i] != NULL; i++)
            {
                printf("%s\n", environ[i]);
            }
            free(line_buffer);
            continue;
        }

        // Check if the specified command exists at the provided path
        char *cmd_name = cmd_argv[0];
        char absolute_path[PATH_MAX];

        if (access(cmd_name, X_OK) == 0)
        {
            // The user entered an absolute or relative path to the command
            strncpy(absolute_path, cmd_name, PATH_MAX);
        }
        else
        {
            // Check if the specified path is valid before proceeding
            if (realpath(cmd_name, absolute_path) == NULL)
            {
                fprintf(stderr, "%s: No such file or directory\n", argv[0]);
                free(line_buffer);
                continue;
            }
        }

        // Create a child process and execute the command
        pid_t fork_processor, wpid;
        int status;
        
        fork_processor = fork();
        
        if (fork_processor == -1)
        {
            perror(argv[0]);
            free(line_buffer);
            continue;
        }
        
        if (fork_processor == 0)
        {
            if (execve(absolute_path, cmd_argv, NULL) == -1)
            {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            wpid = wait(&status);
            if (wpid == -1)
            {
                perror(argv[0]);
            }
        }

        free(line_buffer);
    }
    
    return 0;
}
