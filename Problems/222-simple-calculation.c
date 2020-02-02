
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CHAR 102
#define MAX_ELEMS 10

int main (void){
    char tmp_buffer[MAX_CHAR];
    float result = 0.0;

    char *eof_checker;
    while(eof_checker = fgets(tmp_buffer, MAX_CHAR, stdin)) {
        if(!eof_checker) break;

        char * buffer = (char *) malloc(MAX_CHAR * sizeof(char));
        strcpy(buffer, tmp_buffer);
        
        char * tok = strtok(buffer, " ");
        
        int j = 0;
        while (tok != NULL && j < MAX_ELEMS) {
            // printf("%g\n", atof(tok));
            if(tok != 0x0)
                result += atof(tok);
                //  result += strtold(tok, NULL);
            tok = strtok (NULL, " ");
            
            j++;
        }
        
        result *= 10000;
        result = ceil(result);
        result /= 10000;
        fprintf(stdout, "%.4f\n", result);
        result = 0.0;

        free(tok);
        free(buffer);
    }
    
    return EXIT_SUCCESS;
}