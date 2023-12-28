#include "function.h"

int main(){
    while (true) {
        char* input_string = NULL;
        ssize_t s_len = inputing(&input_string, STDIN_FILENO, 0);

        char* output_string = NULL;

        if (s_len == -1) {
            free(input_string);
            break;
        } else {
            s_len = change(&output_string, input_string);
            write(STDOUT_FILENO, output_string, s_len*sizeof(char));
        }

        free(input_string);
    }
    return 0;
}