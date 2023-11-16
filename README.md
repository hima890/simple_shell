# Simple Shell Project

This project involves creating a simple UNIX command-line interpreter in C that mimics the basic functionalities of the shell (/bin/sh). The shell is designed to meet specific requirements and guidelines outlined below.

## Table of Contents
1. [Requirements](#requirements)
2. [Compilation](#compilation)
3. [Testing](#testing)
4. [Tasks](#tasks)
   - [Task 0: Betty would be proud](#task-0-betty-would-be-proud)
   - [Task 1: Simple shell 0.1](#task-1-simple-shell-01)
   - [Task 2: Simple shell 0.2](#task-2-simple-shell-02)
   - [Task 3: Simple shell 0.3](#task-3-simple-shell-03)
   - [Task 4: Simple shell 0.4](#task-4-simple-shell-04)
   - [Task 5: Simple shell 1.0](#task-5-simple-shell-10)
   - [Task 6: Simple shell 0.1.1](#task-6-simple-shell-011)
   - [Task 7: Simple shell 0.2.1](#task-7-simple-shell-021)
   - [Task 8: Simple shell 0.4.1](#task-8-simple-shell-041)
5. [Authors](#authors)

## Requirements<a name="requirements"></a>

### General
- Editors: vi, vim, emacs
- Compilation on Ubuntu 20.04 LTS using gcc with options -Wall -Werror -Wextra -pedantic -std=gnu89
- Files must end with a new line
- Use Betty style, checked with betty-style.pl and betty-doc.pl
- No memory leaks in the code
- No more than 5 functions per file
- Header files should be include guarded
- Use system calls only when necessary

### Output
- The shell must produce the same output and error messages as /bin/sh

### GitHub
- One project repository per group, avoiding duplicate repository names
- Collaborators should be added to the repository to avoid score deduction

### List of Allowed Functions and System Calls
- [List of allowed functions and system calls](#list-of-allowed-functions-and-system-calls)

## Compilation<a name="compilation"></a>

Compile the shell using the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Testing<a name="testing"></a>

### Interactive Mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Tasks<a name="tasks"></a>

### Task 0: Betty would be proud<a name="task-0-betty-would-be-proud"></a>
- Write a beautiful code that passes the Betty checks

### Task 1: Simple shell 0.1<a name="task-1-simple-shell-01"></a>
- Implement a basic UNIX command line interpreter
- Display a prompt, wait for the user to input a command, and execute it
- Handle the "end of file" condition (Ctrl+D)
- Do not use the PATH or implement built-ins
- Handle errors appropriately

### Task 2: Simple shell 0.2<a name="task-2-simple-shell-02"></a>
- Extend the shell to handle command lines with arguments

### Task 3: Simple shell 0.3<a name="task-3-simple-shell-03"></a>
- Extend the shell to handle the PATH
- Do not call fork if the command doesn't exist

### Task 4: Simple shell 0.4<a name="task-4-simple-shell-04"></a>
- Implement the exit built-in to exit the shell

### Task 5: Simple shell 1.0<a name="task-5-simple-shell-10"></a>
- Implement the env built-in to print the current environment

### Task 6: Simple shell 0.1.1<a name="task-6-simple-shell-011"></a>
- Write a custom getline function using a buffer to minimize calls to the read system call
- Use static variables and avoid using the getline function

### Task 7: Simple shell 0.2.1<a name="task-7-simple-shell-021"></a>
- Avoid using strtok in the shell implementation

### Task 8: Simple shell 0.4.1<a name="task-8-simple-shell-041"></a>
- Modify the exit built-in to handle exit status as an integer argument

## Authors<a name="authors"></a>

- List all individuals who contributed to the repository in the AUTHORS file. Follow the format used in Docker.


bash
/SIMPLE_SHELL
    ├── README.md
    ├── AUTHORS
    ├── .gitignore
    ├── LICENSE
    ├── Build/          # Directory for building the main code
    │   ├── main.c     # Main file
    │   │── main.h     # Header file for function prototypes
    │   ├── function_1.c
    │   ├── function_2.c
    │   ├── function_3.c
    │   ├── ...
    │       
    ├── utility/
    │   ├── function1/                 # Directory for function 1
    │   │   ├── function1.c           # Function 1 implementation
    │   │   ├── function1.h           # Function 1 header
    │   │   ├── function1_test.c      # Function 1 test
    │   │   ├── function1_flowchart.png   # Function 1 flowchart
    │   │   ├── function1_pseudo.txt  # Function 1 pseudo code
    │   │
    │   ├── function2/                 # Directory for function 2
    │   │   ├── function2.c           # Function 2 implementation
    │   │   ├── function2.h           # Function 2 header
    │   │   ├── function2_test.c      # Function 2 test
    │   │   ├── function2_flowchart.png   # Function 2 flowchart
    │   │   ├── function2_pseudo.txt  # Function 2 pseudo code
    │   │   
    │   ├── ...
    ├── man/                           # Manual pages for your shell
    │   ├── shell.1
    ├── flowcharts/                    # Directory for general flowcharts
    │   ├── general_flowchart.png      # General flowchart for the shell
    ├── pseudo_code/                   # Directory for general pseudo code
    │   ├── general_pseudo.txt         # Pseudo code for the shell
    ├── concepts/                      # Directory for general concepts
    │   ├── concept/                   # Directory for concepts
    │   │   ├── function1.c           # Function 1 implementation
    │   │   ├── function1.h           # Function 1 header
    │   │   ├── function1_test.c      # Function 1 test
    │   │   ├── function1_flowchart.png   # Function 1 flowchart
    │   │   ├── function1_pseudo.txt  # Function 1 pseudo code
    │   │
    │   ├── the_main_code/             # Directory for the main code versions
    │   │   ├── main_code_1
    │   │   ├── main_code_2
    │   │   ├── ... 
    │   ├── notes/                      # Directory for general notes
    │   ├── tests/                      # Directory for testing the main code
    
Project Structure
This project follows a structured directory layout to enhance clarity and organization. Below is an overview of each directory:

Build: Contains the main code and header files. The main code is divided into multiple functions for better modularity.

Utility: Houses utility functions organized into separate directories for each function. Each directory includes implementation, header, test, flowchart, and pseudo code files.

Man: Includes manual pages for the shell, such as shell.1.

Flowcharts: Contains general flowcharts representing the overall flow of the shell.

Pseudo_code: Holds general pseudo code outlining the logic and functionality of the shell.

Concepts: Contains directories for various concepts, each comprising implementation, header, test, flowchart, and pseudo code files.

The_Main_Code: Includes versions of the main code, organized into separate directories for each version.

Notes: Reserved for general notes related to the project.

Tests: Dedicated to testing the main code.
