
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
// #include <locale>         // std::locale, std::tolower

#define MAX_TEXT_SIZE 10000
#define MAX_WORD_SIZE 100
#define END_WORD "E-N-D"
#define SEPARATOR " ,.*+/:;?!)('@_\\\"={}<>^#\n0123456789$£€µ§~ù\%[]|&`\t"

int main (void) {
    char* text_buffer = (char*) malloc(sizeof(char) * MAX_TEXT_SIZE);
    char* fileBuffer = (char*) malloc(sizeof(char) * MAX_TEXT_SIZE);

    char *eof_checker;

    char * separator_list = (char *) malloc(sizeof(char) * (0xFF + 150) );
    
    int best_size = -1;
    char * best_word = (char*) malloc(sizeof(char) * MAX_WORD_SIZE);

    char nonAlphachars[0xFF];
    memset(nonAlphachars, 0, 0xFF);
    int i = 0;    
    int c = 1;
    for(; c <= 0xFF; c++) {
        if(!isalpha(c)) {
            nonAlphachars[i++] = c;
        }
    }
    strcpy(separator_list, nonAlphachars);
    strcat(separator_list, SEPARATOR);
    while(fgets(fileBuffer, MAX_TEXT_SIZE, stdin) ) {
        // if(isspace(fileBuffer[0])) {
        //     text_buffer[strcspn(text_buffer, "\n")] = 0;//remove newline
        //     strcat(text_buffer, &fileBuffer[1]);
        //     printf("%s", text_buffer);
        // } else {
            strcpy(text_buffer, fileBuffer);
            // printf("%s", text_buffer);

        char * tok = strtok(text_buffer, separator_list);
        while (tok != NULL) {
            
            if(tok != 0x0 && !strstr(tok, END_WORD)) {
                int current_size = strlen(tok);
                if(current_size > best_size) {
                    best_size = current_size;
                    strcpy(best_word, tok);
                    strcat(best_word, "\0");
                    // printf("New best word: %s <- %s.\n", best_word, tok);

                }
            }

            tok = strtok(NULL, separator_list);
        }


    }


    for(int i = 0; i < best_size; i++){
        if(best_word[i]>=65 && best_word[i]<=90)
            best_word[i]=best_word[i]+32;
        // printf("%d: %c\n", i, best_word[i]);
    }

    std::string res(best_word);
    std::cout << res << std::endl;
    // std::cout<<best_word;//<<std::endl;
    // printf("%s", best_word);
    // fflush(stdout);
}