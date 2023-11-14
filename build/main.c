#include "main.h"

/**
 * main - Simple shell program that reads commands from the standard input or
 *        from a script file, executes them, and prints the result to the
 *        standard output.
 *
 * @argv: Array of strings containing the command-line arguments.
 * @env: Array of strings representing the environment variables.
 * @_arc: Number of arguments
 *
 * Return: The exit status of the shell program.
*/
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
		int i;
		char *cmd_argv[MAX_ARGS];

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
		for (i = 0; cmd_argv[i] != NULL; i++)
		{
			printf("%s\n", cmd_argv[i]);
		}
		if (arc == 0)
		{
			cleanupAndContinue(line_buffer, cmd_argv, arc);
		}

		if (strcmp(cmd_argv[0], "exit") == 0)
		{
			exit_command(cmd_argv, line_buffer, error, arc, argv);
		}
		else if (strcmp(cmd_argv[0], "env") == 0)
		{
			handle_env(env);
			cleanupAndContinue(line_buffer, cmd_argv, arc);
		}
		for (i = 0; cmd_argv[i] != NULL; i++)
		{
			printf("%s\n", cmd_argv[i]);
		}

		hc(argv, env, is_interactive, cmd_argv);

		cleanupAndContinue(line_buffer, cmd_argv, arc);
	}

	if ((is_interactive == 0) && (error == 1))
	{
		return (127);
	}

	return (0);
}

/**
 * hc - Execute the command and handle errors.
 * @argv: Array of command-line arguments.
 * @env: Array of environment variables.
 * @is_interactive: Intger number
 * @cmd_argv: Array of input line arguments
 */
void hc(char *const argv[], char **env, int is_interactive, char *const cmd_argv[])
{
	char *cmd_name = cmd_argv[0];
	pid_t fork_processor, wpid;
	int status;
	char absolute_p[PATH_MAX];
	int error = 0;

	printf("here is heres :%s\n", cmd_name);
	if ((f_pt(cmd_name, absolute_p, is_interactive, &error, cmd_argv, env)) == NULL)
	{
		printf("asdgertert748152\n");
		return;
	}

	fork_processor = fork();

	if (fork_processor == -1)
	{
		perror(argv[0]);
		return;
	}

	if (fork_processor == 0)
	{
		if (cmd_argv[0] == NULL)
		{
			printf("sedfgfddfgfdffdfdfdfg\n");
		}

		if (execve(absolute_p, cmd_argv, env) == -1)
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
		else
		{
			if (WIFEXITED(status))
			{
				error = 2;
			}
		}
	}
}

/**
 * cleanupAndContinue - Free memory and continue to the next iteration.
 * @line_buffer: Buffer containing the command line.
 * @cmd_argv: Array of command-line arguments.
 * @arc: Number of command-line arguments.
 */
void cleanupAndContinue(char *line_buffer, char *cmd_argv[], int arc)
{
	int i;

	free(line_buffer);

	for (i = 0; i < arc; i++)
	{
		free(cmd_argv[i]);
	}
}
