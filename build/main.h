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
#define pt_MAX 4600
#define DEFAULT_pt "/bin:/usr/bin:/sbin:/usr/sbin"

int command_exists(char *cmd_name);
void exit_command(char **ca, char *lb, int error, int arc, char *const *argv);
int isNumeric(const char *str);
void free_resources(char *lb, char **ca, int arc);
int find(char *cn, char *pt, char *ab);
int search_directories(char *cn, char *pc, char *ab);
char *handle_cnf(char *cn, int is, int *er, char *const argv[]);
char *setup_environment(char **env);
char *fc(char *cn, char *ab, int is, int *er, char *const *av[], char *pt);
void handle_exit(char **cmd_argv, char *line_buffer);
void hc(char *const argv[], char **env, int is_interactive, char *const cmd_argv[]);
void cleanupAndContinue(char *line_buffer, char *cmd_argv[], int arc);
void tokenize_input(char *line_buffer, char **cmd_argv, int *argc, int max);
char *f_pt(char *cn, char *ab, int is, int *er, char *const *av, char **env);
void handle_env(char **env);
void print_prompt(void);

#endif /* MAIN_H */
