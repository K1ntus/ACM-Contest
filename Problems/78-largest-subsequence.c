
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 52

int main (void){
    int number_of_tests = 0;
    scanf("%d",&number_of_tests);
    fprintf(stderr, "There will be %d Tests Case.\n", number_of_tests);




    char * word_to_analyze = (char *) malloc(sizeof(char) * MAX_LENGTH);
    scanf("%s\0", word_to_analyze);
    fprintf(stderr, "The word: %s will be analyzed.\n", word_to_analyze);

    char * best_subsequence = (char*) malloc(sizeof(char) * MAX_LENGTH);
    char * current_subsequence = (char*) malloc(sizeof(char) * MAX_LENGTH);

    char last_character_read = word_to_analyze[0];
    best_subsequence[0] = last_character_read;
    current_subsequence[0] = last_character_read;

    int current_length = 1;
    int best_length = 1;

    int i = 1;
    // loop starting from each characters
    // Do not stop at the first misplaced char and just skip it - should be ok
    while(word_to_analyze[i] != '\0' && i < MAX_LENGTH){
        fprintf(stderr, "Current character: %c - Previous Character: %c.\n", word_to_analyze[i], last_character_read);
        fprintf(stderr, "current word state: %s\n", current_subsequence);
        if(word_to_analyze[i] <= last_character_read){
            // fprintf(stderr, "adding this char to the string.\n");
            current_subsequence[current_length] = word_to_analyze[i];
            current_length += 1;
            last_character_read = word_to_analyze[i];

        } else {
            // best_subsequence[current_length] = '\0';
            if(current_length > best_length){
                strcpy(best_subsequence, current_subsequence);
                best_length = current_length;
            }
            // current_length = 0;

        }


        i++;
    }

    fprintf(stderr, "Result String is: %s\n", best_subsequence);

    free(best_subsequence);
    free(word_to_analyze);

    return 0;
}