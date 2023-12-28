#include "function.h"

int inputing(char **s_output, int fd, int endl_status){
    int new_l = MAX_LEN;
    char *line = (char*)malloc(sizeof(char)*new_l); // выделяем память под line размером MAX_LEN = 255 байт
    memset(line, 0 , new_l); //заполняем line нулями
    int i = 0;
    char ch; // выделили 1 байт, чтобы считывать STDIN_FILENO посимвольно
    
    read(fd, &ch, sizeof(ch));
    if(ch == '\n'){ // проверка на \n
        line[i] = '\n';
        *s_output = line;
        return -1;
    }
    while(ch != EOF && ch != '\0' && ch != '\n' ){ 
        if(i >= new_l){ // проверка не достигнута ли максимальная длина строки
            new_l = new_l*2;
            line = (char *)realloc(line, sizeof(char)*new_l); // увеличиваем объем выделенной памяти
        }
        line[i] = ch;
        i++;
        read(fd, &ch, sizeof(ch));  // продолжаем посимвольное считывание

    }
    if(endl_status != 0) { // если нужно вводить строку НЕ один раз
        if(i>=new_l){
            new_l=new_l*2;
            line=(char *)realloc(line, sizeof(char)*new_l);
        }
        line[i]='\n';
        i++;
    }
    if(i >= new_l) {
            new_l=new_l*2;
            line=(char *)realloc(line, sizeof(char)*new_l);
    }
    *s_output = line;

    return i;   
}

size_t change(char **output, char* input) {
    size_t size = strlen(input) + 1;
    char* new_s = (char*)malloc(sizeof(char) * strlen(input) + 1);
    size_t i = 0, j = 0;

    for (i = 0; i < strlen(input); ++i) {
        if (input[i] != 'A' && input[i] != 'E' && input[i] != 'I' && input[i] != 'O' && input[i] != 'Y' && input[i] != 'U'
         && input[i] != 'a' && input[i] != 'e' && input[i] != 'i' && input[i] != 'o' && input[i] != 'y' && input[i] != 'u') {
            
            new_s[i - j] = input[i];

        } else {
            size--;
            j++;
        }
    }
    new_s[i - j] = '\n';

    *output = new_s;
    return size;
}
