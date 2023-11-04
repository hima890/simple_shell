#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> // for opendir and readdir
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    char *path = getenv("PATH");

    if (path == NULL) {
        perror("PATH environment variable not found.");
        return 1;
    }

    const char *delim = ":"; // Delimiter to separate directory paths
    char *token = strtok(path, delim);

    while (token != NULL) {
        DIR *dir = opendir(token);
        if (dir) {
            struct dirent *ent;
            while ((ent = readdir(dir)) != NULL) {
                // Check if the current entry is a regular file
                if (ent->d_type == DT_REG) {
                    for (int i = 1; i < argc; i++) {
                        if (strcmp(ent->d_name, argv[i]) == 0) {
                            printf("File %s found in directory %s\n", argv[i], token);
                        }
                    }
                }
            }
            closedir(dir);
        } else {
            perror("Could not open directory.");
        }

        token = strtok(NULL, delim); // Move to the next directory path
    }

    return 0;
}
