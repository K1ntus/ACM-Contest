
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100
#define MAX_ELEMS 10

int main (void){
    int number_of_tests = 5;
    // scanf("%d",&number_of_tests);
    fprintf(stderr, "There will be %d Tests Case.\n", number_of_tests);

    char tmp_buffer[MAX_CHAR-1];
    float result = 0.0;

    for(int i = 0; i < number_of_tests; i++){
        fgets(tmp_buffer, MAX_CHAR-1, stdin);
        char * buffer = (char *) malloc(MAX_CHAR * sizeof(char));
        strcpy(buffer, tmp_buffer);
        // if(scanf("%f[^\n]%c", &buffer[nb_elems]) != 1)
        //     break;
        // if(buffer[nb_elems] == '\n')
        //     break;
        // result += buffer[nb_elems];
        char * tok = strtok(buffer, " ");
        // result += strtod(tok, 0x0);
        int j = 0;
        while (tok != NULL && j < 10) {
            printf("%g\n", atof(tok));
            if(tok != 0x0)
                result += atof(tok);
            tok = strtok (NULL, " ");
            // result += strtod(tok, 0x0);
            j++;
        }
        free(tok);
        free(buffer);
        fprintf(stderr, "result is: %.4f\n\n", result);
        result = 0.0;
    }
    
        // free(tok);
    return EXIT_SUCCESS;
}