
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
// #include <locale>         // std::locale, std::tolower

#define MAX_TEXT_SIZE 10000
#define MAX_WORD_SIZE 100
#define END_WORD "E-N-D"
#define SEPARATOR " ,.*+/:;?!)('@_\\\"={}<>^#\n0123456789$£€µ§~ù\%[]|&`\t"

void PrintResult(char * best_word, int best_size) {

    for(int i = 0; i < best_size; i++){
        if(best_word[i]>=65 && best_word[i]<=90)
            best_word[i]=best_word[i]+32;
    }

    std::string res(best_word);
    std::cout << res << std::endl;
}


int main (void) {
    char* text_buffer = (char*) malloc(sizeof(char) * MAX_TEXT_SIZE);
    char* fileBuffer = (char*) malloc(sizeof(char) * MAX_TEXT_SIZE);

    char *eof_checker;

    char * separator_list = (char *) malloc(sizeof(char) * (0xFF + 150) );
    
    int best_size = -1;
    char * best_word = (char*) malloc(sizeof(char) * MAX_WORD_SIZE);

    // char nonAlphachars[0xFF];
    // memset(nonAlphachars, 0, 0xFF);
    // int i = 0;    
    // int c = 1;
    // for(; c <= 0xFF; c++) {
    //     if(!isalpha(c)) {
    //         nonAlphachars[i++] = c;
    //     }
    // }
    // strcpy(separator_list, nonAlphachars);


    strcat(separator_list, SEPARATOR);
    while(fgets(fileBuffer, MAX_TEXT_SIZE, stdin) ) {
        strcpy(text_buffer, fileBuffer);

        char * tok = strtok(text_buffer, separator_list);
        while (tok != NULL) {
            
            if(tok && !strstr(tok, END_WORD)) {
                int current_size = strlen(tok);
                if(current_size > best_size) {
                    best_size = current_size;
                    strcpy(best_word, tok);
                    strcat(best_word, "\0");

                }
            } else {
                PrintResult(best_word, best_size);
                return 0;
            }

            tok = strtok(NULL, separator_list);
        }


    }

    PrintResult(best_word, best_size);

    free(text_buffer);
    free(fileBuffer);
    free(eof_checker);
    free(separator_list);
    free(best_word);
    return 0;
}