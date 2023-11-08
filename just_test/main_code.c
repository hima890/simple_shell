#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>


int main(int argc, char * const argv[])
{
    while (1)
    {
        /* Init the read buffer*/
        char *line_buffer = NULL;
        size_t line_buffer_size = 0;
        ssize_t read;
        printf("$ ");
        read = getline(&line_buffer, &line_buffer_size, stdin);
        line_buffer[read - 1] = '\0';  /* Remove the newline character from the buffer */
        if (read == -1) /* Check for the Ctrl+d */
        {
            perror("The Ctrl+d !!");
        }
        
        /* Tokenize the input line */
        char *token = strtok(line_buffer, " "); /* Token by " "*/
        int argc = 0; /* Argument counter */
        char *cmd_argv[100]; /* Adjust the size as needed */
        while (token != NULL && argc < 100) /* Loop throwe the buffer and tokenize it */
        {
            if (strcmp(token, "") != 0)
            {
                cmd_argv[argc] = token;
                argc++;
            }
            token = strtok(NULL, " ");
        }
        cmd_argv[argc] = NULL; /* Null-terminate the argument array */

        if (argc == 0)
        {
            free(line_buffer);
            continue;  // Empty command, continue to the next iteration
        }

        /* Check for the exit input */
        if (strcmp(cmd_argv[0], "exit") == 0)
        {
            if (cmd_argv[1] == NULL) /* Check if no status profid */
            {
                free(line_buffer);
                exit(0); /* Exit with 0 status */
            }
            /* If status code profid */
            int exit_status = atoi(cmd_argv[1]); /* Convert the status code to intiger */
            free(line_buffer);
            exit(exit_status);
        }
        
        /* Check for the env input */
        if (strcmp(cmd_argv[0], "env") == 0)
        {
            extern char **environ;
            int i = 0;
            for (i; environ[i] != NULL; i++)
            {
                printf("%s\n", environ[i]);
            }
            
        }
        
        /* Search for the command path assming first token is the command path */
        char *path = getenv("PATH"); /* Get the path info*/
        if (path == NULL) /* If the path empty*/
        {
            perror("The path var. is empty!!");
            free(line_buffer);
            exit(-1); /* Exit with 0 status */

        }
        else
        {
            char *path_copy = strdup(path);  /* Make a copy of the PATH */
            int command_found_falg = 0;  /* Flag to track if the command is found */
            /* Tokenize the path dirctres */
            const char *delim_2 = ":";
            char *path_token = strtok(path_copy, delim_2);
            char *cmd_name = cmd_argv[0];  /* First token is the command name */
            char absolute_path[PATH_MAX];
            printf("The command: %s\n", cmd_name);
            while (path_token != NULL) /* Loop throwe the path and tokenize it */
            {
                DIR *command_dir = opendir(path_token);
                if (command_dir)
                {
                    struct dirent *ent;
                    while ((ent = readdir(command_dir)) != NULL)
                    {
                        if (ent->d_type == DT_REG)
                        {
                            if (strcmp(ent->d_name, cmd_name) == 0)
                            {
                                sprintf(absolute_path, "%s/%s", path_token, ent->d_name);
                                printf("File %s found in directory %s\n", cmd_argv[0], absolute_path);
                                command_found_falg = 1;
                                break;
                            }
                        }
                    }
                    closedir(command_dir);
                } 
                else
                {
                    printf("Could not open the command directory: %s", path_token);
                }
                path_token = strtok(NULL, delim_2); /* Next command to tokenize */
                
                if (command_found_falg == 1)
                {
                    // printf("Break with more paths the command found\n");
                    break;
                }
            }
            free(path_copy); /* Free the duplicated path */
            if (command_found_falg  == 0) /* Check if the commund not found*/
            {
                printf("%s: command not found\n", cmd_name);
            }
            else
            {
                /* Start the sub processer for the command path */
                pid_t fork_processer, wpid;
                int status;
                fork_processer = fork();
                if (fork_processer == -1) /* Chech the forcking */
                {
                    perror("Fork_processer field!!");
                    exit(-1);
                }
                if (fork_processer == 0) /* Check the create of the sub-processe */
                {
                    if (execve(absolute_path, cmd_argv, NULL) == -1)
                    {
                        /* If the execve is falid */
                        perror("Execve Error");
                        exit(-1); /* Terminate the child process */
                    }
                    
                    exit(0); /* Terminate the child process */
                }
                else
                {
                    wpid = wait(&status);
                    if (wpid == -1)
                    {
                        perror("wait");
                        exit(-1);
                    }
                }
                
                

            }
        }
        
        

        free(line_buffer);
    }
    
    return (0);
}