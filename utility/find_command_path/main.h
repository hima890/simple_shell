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
char* find_command_path(const char *cmd_name, char *absolute_path, const char *env_path);

#endif /* MAIN_H */