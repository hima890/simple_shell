#ifndef MAIN_H
#define MAIN_H

int command_exists(char *cmd_name);
void exit_command(char **cmd_argv, char *line_buffer);
void handle_exit(char **cmd_argv, char *line_buffer);
void tokenize_input(char *line_buffer, char **cmd_argv, int *argc, int max);
char* find_command_path(const char *cmd_name, char *absolute_path, const char *env_path);
void handle_env(char **env);
void print_prompt();

#endif /* MAIN_H */
