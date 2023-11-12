#ifndef MAIN_H
#define MAIN_H
#define MAX_ARGS 100
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

int command_exists(char *cmd_name);
static int search_in_directory(const char *cmd_name, const char *directory, char *absolute_path);
char* find_command_path(const char *cmd_name, char *absolute_path, const char *env_path);

#endif /* MAIN_H */