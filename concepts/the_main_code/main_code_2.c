#include "main.h"
int main(int _arc, char *const argv[], char **env)
{
	int is_interactive = isatty(STDIN_FILENO);
	int error = 0;
	while (1)
	{
		char *line_buffer = NULL;
		size_t line_buffer_size = 0;
		ssize_t read;
		int arc = 0;
		char *cmd_argv[MAX_ARGS];
		char absolute_path[PATH_MAX];
		char *cmd_name;

		pid_t fork_processor, wpid;
		int status;
		int i;

		(void)_arc;
		print_prompt();
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
			exit_command(cmd_argv, line_buffer, error, arc, argv);
		}
		else if (strcmp(cmd_argv[0], "env") == 0)
		{
			handle_env(env);
			for (i = 0; i < arc; i++)
			{
				free(cmd_argv[i]);
			}
			free(line_buffer);
			continue;
		}
		cmd_name = cmd_argv[0];

		if ((f_path(cmd_name, absolute_path, is_interactive, &error, argv, env)) == NULL)
		{
			free(line_buffer);
			for (i = 0; i < arc; i++)
			{
				free(cmd_argv[i]);
			}
			if (is_interactive == 0)
			{
				error = 1;
			}
			continue;
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
			else
			{
				if (WIFEXITED(status))
				{
					error = 2;
				}
			}
		}
		free(line_buffer);
		for (i = 0; i < arc; i++)
		{
			free(cmd_argv[i]);
		}
	}
	if ((is_interactive == 0) && (error == 1))
	{
		return (127);
	}
	return (0);
}