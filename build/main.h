#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

#define MAX_ARGS 16000

int command_exists(char *cmd_name);
void exit_command(char **cmd_argv, char *line_buffer, int error, int arc);
void handle_exit(char **cmd_argv, char *line_buffer);
void tokenize_input(char *line_buffer, char **cmd_argv, int *argc, int max);
char *f_path(char *cmd, char *abs, int is, int *er, char *const *argv, char **env);
void handle_env(char **env);
void print_prompt();

#endif /* MAIN_H */
