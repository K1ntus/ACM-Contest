
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CHAR 102
#define MAX_ELEMS 10
#define MIN_ELEMS 1

int main (void){
    char tmp_buffer[MAX_CHAR];
    long double result = 0.0;

    char *eof_checker;
    int consecutive_case = 0;

    while(eof_checker = fgets(tmp_buffer, MAX_CHAR, stdin)) {
        if(!eof_checker) break;
        else if(!strcmp(tmp_buffer, "\n")) continue;
        else if(eof_checker[0] == EOF) break;
        else
            if(consecutive_case > 0) printf("\n");// && tmp_buffer[0] != EOF) printf("\n");
            else consecutive_case = 1;

        char * buffer = (char *) malloc(MAX_CHAR * sizeof(char));
        strcpy(buffer, tmp_buffer);

        for(int j = 0; j < MAX_ELEMS; j++){
            if(buffer[0] == '\n') break;
            result += strtold(buffer, &buffer);
        }
        
        // char * tok = strtok(buffer, " ");
        
        // int j = 0;
        // while (tok != NULL && tok != "\n" && j < MAX_ELEMS) {
        //     if(tok != 0x0)
        //         result += strtold(tok, NULL);
        //     tok = strtok (NULL, " ");
        //     j++;
        // }
        
        // result *= 10000;
        // printf("previous result:%Lf\n", result);
        
        result = result * 10000.0;
        // printf("%Lf->", result);
        result = truncl(result);
        result = std::ceil(result);
        // printf("%Lf->", result);
        result = result / 10000.0;
        // result /= 10000;
        fprintf(stdout, "%.4Lf\n", result);
        result = 0.0;

        // free(tok);
        // free(buffer);
    }
    
    return EXIT_SUCCESS;
}