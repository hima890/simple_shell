#include <stdio.h>

// Declare the global environ variable
extern char** environ;

int main(int argc, char* argv[], char* envp[]) {
    // Print the address of envp
    printf("Address of envp: %p\n", envp);

    // Print the address of environ
    printf("Address of environ: %p\n", environ);

    return 0;
}
