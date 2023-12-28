#ifndef function_h
#define function_h
#include <stdio.h>
#include <fcntl.h> //files
#include <stdlib.h> //malloc
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h> //pid_t
#include <string.h>
#include <sys/wait.h>

#define MAX_LEN 255 // max length for file's names

int inputing(char **output_name, int fd, int endl_status);

size_t change(char **output, char* input);


#endif