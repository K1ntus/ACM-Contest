
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
// #include <locale>         // std::locale, std::tolower

#define MAX_TEXT_SIZE 15000
#define MAX_WORD_SIZE 150
#define END_WORD "E-N-D"

int main (void) {
    char* text_buffer = (char*) malloc(sizeof(char) * MAX_TEXT_SIZE);

    char *eof_checker;
    while( eof_checker = fgets(text_buffer, MAX_TEXT_SIZE, stdin) );
    
    char * tok = strtok(text_buffer, " ");
    
    int best_size = -1;
    char * best_word = (char*) malloc(sizeof(char) * 100);
    while (tok != NULL) {
        
        if(tok != 0x0 && !strstr(tok, END_WORD)) {
            int current_size = strlen(tok);
            if(current_size > best_size) {
                best_size = current_size;
                strcpy(best_word, tok);

                // printf("New best word: %s <- %s.\n", best_word, tok);

            }
        }

        tok = strtok(NULL, " ");
    }

    for(int i = 0; i < best_size; i++){
        if(best_word[i]>=65 && best_word[i]<=90)
            best_word[i]=best_word[i]+32;
    }
    std::cout<<best_word<<std::endl;
    // printf("%s", best_word);
    // fflush(stdout);
}