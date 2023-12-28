#include "function.h"

int main() {
    write(STDOUT_FILENO, "Enter the first filename with file extension(.txt or .doc or .rtf): ", 69);

    char* Filename_1 = NULL;

    if (inputing(&Filename_1, STDIN_FILENO, 0) <= 0) {
        perror("Trying to create 0-value string: ");
        exit(-1);
    }

    int f1_output = open(Filename_1, O_WRONLY);
    if (f1_output == -1) {
        fprintf(stderr, "Can't open the file: %s", Filename_1);
    }
    free(Filename_1);

    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Call pipe was ended with erroe: ");
        exit(-1);
    }

    pid_t pid_1 = fork();

    if (pid_1 == 0) {
        //first child
        close(pipe1[1]); //for writing
        close(pipe2[0]); //for second child
        close(pipe2[1]);
        
        if (dup2(pipe1[0], STDIN_FILENO) == -1) {
            perror("dup2 error ");
            exit(-1);
        }
        if (dup2(f1_output, STDOUT_FILENO) == -1) {
            perror("dup2 error ");
            exit(-1);
        }
        if(dup2(f1_output, STDERR_FILENO)==-1){
            perror("dup2 erorr ");
            exit(-1);
        }

        if(execl("./child_1", "./child_1", NULL) == -1) {
            perror("execl error");
            exit(-1);
        }
    } else {    //parent
        write(STDOUT_FILENO, "\nEnter the second filename with file extension(.txt or .doc or .rtf): ", 71);
        char* Filename_2 = NULL;

        if (inputing(&Filename_2, STDIN_FILENO, 0) <= 0) {
            perror("Trying to create 0-value string: ");
            exit(-1);
        }

        int f2_output = open(Filename_2, O_WRONLY);
        if (f2_output == -1) {
        fprintf(stderr, "Can't open the file: %s", Filename_1);
        }
        free(Filename_2);

        pid_t pid_2 = fork();
        if (pid_2 == 0) {
            //second child
            close(pipe2[1]);//for writing
            close(pipe1[0]);//for first child
            close(pipe1[1]);

        if (dup2(pipe2[0], STDIN_FILENO) == -1) {
            perror("dup2 error ");
            exit(-1);
        }
        if (dup2(f2_output, STDOUT_FILENO) == -1) {
            perror("dup2 error ");
            exit(-1);
        }
        if(dup2(f2_output, STDERR_FILENO)==-1){
            perror("dup2 erorr ");
            exit(-1);
        }

        if(execl("./child_2", "./child_2", NULL) == -1) {
            perror("execl error");
            exit(-1);
        }
        } else {    //parent
            close(pipe1[0]);
            close(pipe2[0]);

            write(STDOUT_FILENO, "Enter string: ", 15);
            while (true) {
                char* s = NULL;
                int s_len = inputing(&s, STDIN_FILENO, 1);
                if (s_len == -1) {
                    if (write(pipe1[1], s, 1) == -1) {
                        perror("write error ");
                        exit(-1);
                    }
                    if (write(pipe2[1], s, 1) == -1) {
                        perror("write error ");
                        exit(-1);
                    }
                    
                    free(s);
                    break;
                } else {
                    if (s_len <= 11) {
                        if (write(pipe1[1], s, sizeof(char) * s_len) == -1) {
                            perror("write error ");
                            exit(-1);
                        }
                    } else if (write(pipe2[1], s, sizeof(char) * s_len) == -1) {
                            perror("write error ");
                            exit(-1);
                    }
                }

                free(s);
            }
            close(f2_output);
        }
    }
    
    close(pipe1[1]);
    close(pipe2[1]);
    close(f1_output);
    wait(NULL);
}


