#ifndef MAIN_H
#define MAIN_H

int command_exists(char *cmd_name);
void exit_command(char **cmd_argv, char *line_buffer);
void handle_exit(char **cmd_argv, char *line_buffer);
void tokenize_input(char *line_buffer, char **cmd_argv, int *argc, int max);

#endif /* MAIN_H */