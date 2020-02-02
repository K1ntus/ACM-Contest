
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
// #include <locale>         // std::locale, std::tolower

#define MAX_TEXT_LINES 5000
#define MAX_LINE_SIZE 200
#define END_WORD EOF
#define WORD_SEPARATOR " "

typedef struct {
    char ** word_list;
    int size_list;
} dictionnary_struct;

dictionnary_struct * InitDictionnary(void) {
    dictionnary_struct * dico = (dictionnary_struct *) malloc(sizeof(dictionnary_struct));
    dico->size_list = 0;
    dico->word_list = (char **) malloc(sizeof(char *) * MAX_LINE_SIZE * MAX_TEXT_LINES);

    return dico;
}

void WordToInsensitive(char * word) {

    for(int i = 0; word[i]; i++){
        if(word[i]>=65 && word[i]<=90)
            word[i]=word[i]+32;
        // printf("%d: %c\n", i, best_word[i]);
    }
}

void FreeDictionnary(dictionnary_struct * dico) {
    free(dico->word_list);
    free(dico);
} 

bool IsWordAlreadyInDictionnary(dictionnary_struct dictionnary, const char * wordToCompare) {
    
}

void sort_words(char *words[], int count)
{
    char *x;

    for (int i = 0; i<count; i++)
    {
        for (int j = i + 1; j<count; j++)
        {
            if (strcmp(words[i], words[j]) < 0)
            {
                x = words[j];
                words[j] = words[i];
                words[i] = x;
            }
        }

    }
}

void AddWordToDictionnary(dictionnary_struct * dictionnary, const char * wordToAdd) {
    char * tmp;
    strcpy(tmp, wordToAdd);
    WordToInsensitive(tmp);
    for(int i = 0; i < dictionnary->size_list; i++) {
        if(strcmp(dictionnary->word_list[i], tmp)) return;
    }

    dictionnary->size_list += 1;
    strcpy(dictionnary->word_list[dictionnary->size_list], tmp);
}

void PrintDictionnary(dictionnary_struct dictionnary) {
    for(int i = 0; i < dictionnary.size_list; i++)
        fprintf(stdout, "%s", dictionnary.word_list[i]);
}

int main (void) {
    dictionnary_struct * dictionnary = InitDictionnary();
    char* text_buffer = (char*) malloc(sizeof(char) * MAX_LINE_SIZE);

    char *eof_checker;
    int nb_lines = 0;
    while( (eof_checker = fgets(text_buffer, MAX_LINE_SIZE, stdin)) && nb_lines < MAX_TEXT_LINES) {
        char * tok = strtok(text_buffer, WORD_SEPARATOR);
        while (tok != NULL) {
            
            if(tok != 0x0) {
                AddWordToDictionnary(dictionnary, tok);
                // int current_size = strlen(tok);
                // if(current_size > 0) {
                //     // best_size = current_size;
                //     // strcpy(best_word, tok);
                //     // strcat(best_word, "\0");
                //     // printf("New best word: %s <- %s.\n", best_word, tok);
                // }
            }

            tok = strtok(NULL, WORD_SEPARATOR);
        }
        nb_lines += 1;
    }

    PrintDictionnary(*dictionnary);
    
    // std::string res(best_word);
    // std::cout << res << std::endl;
    // std::cout<<best_word;//<<std::endl;
    // printf("%s", best_word);
    // fflush(stdout);

    FreeDictionnary(dictionnary);
}