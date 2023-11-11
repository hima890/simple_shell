#include "main.h"
/**
 * main - program entry point .
 * 
 * @argc:the number of arguments in passed to main.
 * @argv:an array of char arguments passed to main
 * @env:env varaibles 
 * 
 * Description:
 * a test of the handle_env function (replaced the handle env part
 * with the function) which is a function that prints env vars.
 * 
 * Return: 0 Always if seccuss.
 * 
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
            handle_env(env);
            free(line_buffer);
            continue;
        }

        
    }

    return (0);
}