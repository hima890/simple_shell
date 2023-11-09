#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char * const argv[]) {
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    ssize_t read;

    while (1) {
        memset(line_buffer, 0, line_buffer_size);  // Clear the line_buffer
        printf("$ ");
        read = getline(&line_buffer, &line_buffer_size, stdin);

        if (read == -1) {
            perror("Read the line!");
            break;
        }

        line_buffer[read - 1] = '\0';  // Remove the newline character

        if (strcmp(line_buffer, "q") == 0) {
            free(line_buffer);
            exit(0);
        } else {
            // Tokenize the input line and find the directory of the command
            char *token = strtok(line_buffer, " ");
            char *cmd_name = token;  // First token is the command name

            char *path = getenv("PATH");
            if (path == NULL) {
                perror("PATH environment variable not found.");
            } else {
                printf("PATH environment variable found.\n");
                char *path_copy = strdup(path);  // Make a copy of the PATH

                const char *delim_2 = ":";
                char *token_2 = strtok(path_copy, delim_2);
                int found = 0;  // Flag to track if the command is found

                while (token_2 != NULL) {
                    // printf("%s \n", token_2);
                    DIR *dir = opendir(token_2);
                    if (dir) {
                        struct dirent *ent;
                        while ((ent = readdir(dir)) != NULL) {
                            if (ent->d_type == DT_REG) {
                                if (strcmp(ent->d_name, cmd_name) == 0) {
                                    char absolute_path[PATH_MAX];
                                    sprintf(absolute_path, "%s/%s", token_2, ent->d_name);
                                    printf("File %s found in directory %s\n", token, absolute_path);
                                    found = 1;
                                    break;
                                }
                            }
                        }
                        closedir(dir);
                    } else {
                        printf("Could not open directory.");
                    }
                    token_2 = strtok(NULL, delim_2);
                }

                free(path_copy);  // Free the duplicated path
                if (!found) {
                    printf("Command not found in any directory.\n");
                }
            }
        }
    }

    free(line_buffer);
    return 0;
}
