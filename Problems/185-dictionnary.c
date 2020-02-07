
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
// #include <locale>         // std::locale, std::tolower

#define MAX_TEXT_LINES 5500
#define MAX_LINE_SIZE 250
#define MAX_DISTINCTS_WORDS 5000
#define END_WORD EOF
#define WORD_SEPARATOR " .:\"\n?!/\\()[];"

typedef struct {
    char ** word_list;
    int size_list;
} dictionnary_struct;

dictionnary_struct * InitDictionnary(void) {
    dictionnary_struct * dico = (dictionnary_struct *) malloc(sizeof(dictionnary_struct));
    dico->size_list = 0;
    dico->word_list = (char **) malloc(sizeof(char *) * MAX_DISTINCTS_WORDS);

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

// Defining comparator function as per the requirement 
static int myCompare(const void* a, const void* b) 
{ 
  
    // setting up rules for comparison 
    return strcmp(*(const char**)a, *(const char**)b); 
}
  
// Function to sort the array 
void sort(char* arr[], int n) 
{ 
    // calling qsort function to sort the array 
    // with the help of Comparator 
    qsort(arr, n, sizeof(const char*), myCompare); 
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
    char * tmp = (char *) malloc( sizeof(char) * MAX_LINE_SIZE);
    strcpy(tmp, wordToAdd);
    WordToInsensitive(tmp);
    for(int i = 0; i < dictionnary->size_list; i++) {
        if(!strcmp(dictionnary->word_list[i], tmp)){
            free(tmp);
            return;
        } 
    }

    // printf("---> Added Word: %s\n", tmp);
    dictionnary->word_list[dictionnary->size_list] = tmp;
    dictionnary->size_list += 1;
}

void PrintDictionnary(dictionnary_struct dictionnary) {
    // printf("** Printing the Dictionnary.\n");
    for(int i = 0; i < dictionnary.size_list; i++)
        fprintf(stdout, "%s\n", dictionnary.word_list[i]);
    // printf("** End printing.\n");
}

int main (void) {
    dictionnary_struct * dictionnary = InitDictionnary();
    char* text_buffer = (char*) malloc(sizeof(char) * MAX_LINE_SIZE);

    char *eof_checker;
    int nb_lines = 0;
    while( (eof_checker = fgets(text_buffer, MAX_LINE_SIZE, stdin)) && nb_lines < MAX_TEXT_LINES) {
        char * tok = strtok(text_buffer, WORD_SEPARATOR);
        while (tok != NULL) {
            
            if(tok != 0x0 && strcmp(tok, "\n")) {
                // fprintf(stderr, "-> Current word is %s\n", tok);
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

    sort(dictionnary->word_list, dictionnary->size_list);

    PrintDictionnary(*dictionnary);

    FreeDictionnary(dictionnary);

    return 0;
}