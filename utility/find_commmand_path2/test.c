#include "main.h"
/**
 * Main function for a simple shell program. This shell supports both interactive
 * and non-interactive modes, reading user input, processing commands, and executing
 * them in child processes. It recognizes built-in commands like "exit" to terminate
 * the shell with an optional exit status and "env" to display environment variables.
 * For other commands, it searches for the command's absolute path using the PATH
 * environment variable and executes it in a child process.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line arguments, including the program name.
 * @env: An array of environment variables.
 * Return: 0 upon successful execution or an error code if an issue occurs.
 */

int main(int argc, char * const argv[], char **env)
{
    while (1)
    {
        char *line_buffer = NULL;
        size_t line_buffer_size = 0;
        ssize_t read;
        int is_interactive = isatty(STDIN_FILENO);

        if (is_interactive)
        {
            printf("$ ");
        }
        if ((read = getline(&line_buffer, &line_buffer_size, stdin)) == -1)
        {
            if (feof(stdin))
            {
                free(line_buffer);
                break;
            }
            else
            {
                perror(argv[0]);
                free(line_buffer);
                continue;
            }
        }
        if ((read > 0) && (line_buffer[read - 1] == '\n'))
        {
            line_buffer[read - 1] = '\0';
        }

        int argc = 0;
        char *cmd_argv[MAX_ARGS];
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
        cmd_argv[argc] = NULL;
        if (argc == 0)
        {
            free(line_buffer);
            continue;
        }
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
        if (strcmp(cmd_argv[0], "env") == 0)
        {
            unsigned int i = 0;
            while (env[i] != NULL)
            {
                printf("%s\n", env[i]);
                i++;
            }
            free(line_buffer);
            continue;
        }
        char *cmd_name = cmd_argv[0];
        char absolute_path[PATH_MAX];
        char *path = getenv("PATH");

        // Use the new function to find the command path
        char *cmd_path = find_command_path(cmd_name, absolute_path, path);

        if (cmd_path == NULL)
        {
            free(line_buffer);
            continue;
        }

        pid_t fork_processor, wpid;
        int status;
        fork_processor = fork();
        if (fork_processor == -1)
        {
            perror(argv[0]);
            free(line_buffer);
            free(cmd_path);
            continue;
        }
        if (fork_processor == 0)
        {
            // Child process
            if (execve(cmd_path, cmd_argv, NULL) == -1)
            {
                perror(argv[0]);
                free(line_buffer);
                free(cmd_path);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            // Parent process
            wpid = wait(&status);
            if (wpid == -1)
            {
                perror(argv[0]);
            }
        }
        free(line_buffer);
        free(cmd_path);
    }
    return 0;
}
