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

int main(int _arc, char *const argv[], char **env)
{
	while (1)
	{
		char *line_buffer = NULL;
		size_t line_buffer_size = 0;
		ssize_t read;
		int arc = 0;
		char *cmd_argv[MAX_ARGS];
		char absolute_path[PATH_MAX];
		char *cmd_name;
		int is_interactive = isatty(STDIN_FILENO);
		pid_t fork_processor, wpid;
		int status;
		int i;

		(void)_arc;
		if (is_interactive)
		{
			printf("$ ");
		}

		read = getline(&line_buffer, &line_buffer_size, stdin);
		if (read == -1)
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

		tokenize_input(line_buffer, cmd_argv, &arc, MAX_ARGS);

		if (arc == 0)
		{
			free(line_buffer);
			continue;
		}

		if (strcmp(cmd_argv[0], "exit") == 0)
		{
			exit_command(cmd_argv, line_buffer);
		}
		else if (strcmp(cmd_argv[0], "env") == 0)
		{
			extern char **environ;
			int i;

			for (i = 0; environ[i] != NULL; i++)
			{
				printf("%s\n", environ[i]);
			}
			for (i = 0; i < arc; i++)
			{
				free(cmd_argv[i]);
			}
			free(line_buffer);
			continue;
		}

		cmd_name = cmd_argv[0];

		if (command_exists(cmd_name))
		{
			strncpy(absolute_path, cmd_name, PATH_MAX);
		}
		else
		{
			char *path = getenv("PATH");
			char *path_copy;
			char *path_token;
			const char *delim_2 = ":";
			int command_found_flag = 0;

			if (path == NULL)
			{
				perror(argv[0]);
				free(line_buffer);
				for (i = 0; i < arc; i++)
				{
					free(cmd_argv[i]);
				}
				continue;
			}

			path_copy = strdup(path);
			path_token = strtok(path_copy, delim_2);

			while (path_token != NULL)
			{
				DIR *command_dir = opendir(path_token);

				if (command_dir)
				{
					struct dirent *ent;
					while ((ent = readdir(command_dir)) != NULL)
					{
						if (ent->d_type == DT_REG && strcmp(ent->d_name, cmd_name) == 0)
						{
							snprintf(absolute_path, PATH_MAX, "%s/%s", path_token, ent->d_name);
							command_found_flag = 1;
							break;
						}
					}
					closedir(command_dir);
				}
				else
				{
					perror(argv[0]);
				}
				path_token = strtok(NULL, delim_2);
				if (command_found_flag == 1)
				{
					break;
				}
			}
			free(path_copy);
			if (command_found_flag == 0)
			{
				fprintf(stderr, "%s: %d: %s: not found\n", argv[0], __LINE__, cmd_name);
				free(line_buffer);
				for (i = 0; i < arc; i++)
				{
					free(cmd_argv[i]);
				}
				continue;
			}
		}
		fork_processor = fork();

		if (fork_processor == -1)
		{
			perror(argv[0]);
			
			for (i = 0; i < arc; i++)
			{
				free(cmd_argv[i]);
			}
			free(line_buffer);
			continue;
		}

		if (fork_processor == 0)
		{
			if (execve(absolute_path, cmd_argv, env) == -1)
			{
				perror(argv[0]);
				free(line_buffer);
				for (i = 0; i < arc; i++)
				{
					free(cmd_argv[i]);
				}
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
		for (i = 0; i < arc; i++)
		{
			free(cmd_argv[i]);
		}
	}

	return (0);
}
