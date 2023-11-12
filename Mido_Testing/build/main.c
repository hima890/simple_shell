#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include "main.h"
#define MAX_ARGS 16000

int main(int argc, char * const argv[], char **env) {
    while (1) {
        char *line_buffer = NULL;
        size_t line_buffer_size = 0;
        ssize_t read;

        print_prompt();

        if ((read = getline(&line_buffer, &line_buffer_size, stdin)) == -1) {
            // Handle errors and end of file
            perror(argv[0]);
            free(line_buffer);
            break;
        }

        // Tokenize input
        int argc = 0;
        char *cmd_argv[MAX_ARGS];
        tokenize_input(line_buffer, cmd_argv, &argc);

        if (argc == 0) {
            // No command provided, continue to the next iteration
            free(line_buffer);
            continue;
        }

        // Handle built-in commands
        if (strcmp(cmd_argv[0], "exit") == 0) {
            handle_exit(argv[0], line_buffer);
            // The handle_exit function does not return, but if it did, you'd need to free line_buffer here
        } else if (strcmp(cmd_argv[0], "env") == 0) {
            handle_env(env);
            free(line_buffer);
            continue;
        }

        // Find command path
        char absolute_path[PATH_MAX];
        if (!find_command_path(cmd_argv[0], absolute_path, getenv("PATH"))) {
            fprintf(stderr, "%s: %d: %s: not found\n", argv[0], __LINE__, cmd_argv[0]);
            free(line_buffer);
            continue;
        }

        // Execute the command
        execute_command(absolute_path, cmd_argv, argv[0]);

        free(line_buffer);
    }

    return 0;
}
