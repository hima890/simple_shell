#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#define MAX_ARGS 100

int command_exists(char *cmd_name);
char *f_path(char *cmd, char *abs, int is, int *er, char *const *argv);

#endif /* MAIN_H */