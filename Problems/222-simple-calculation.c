
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100
#define MAX_ELEMS 10

int main (void){
    int number_of_tests = 0;
    // scanf("%d",&number_of_tests);
    fprintf(stderr, "There will be %d Tests Case.\n", number_of_tests);

    float buffer[10];
    int nb_elems = 0;
    float result = 0.0;
    for(; nb_elems < 10; nb_elems++) {
        if(scanf("%f", &buffer[nb_elems]) != 1)
            break;
        result += buffer[nb_elems];
    }
    fprintf(stderr, "result is: %.4f\n\n", result);
    // fprintf(stderr, "Buffer: %s\n", buffer);

    // char *token;
   
    // token = strtok(buffer, " ");
    
    // float sum = 0;
    // /* walk through other tokens */
    // while( token != NULL ) {
    //     printf( "Current Token: %s\n", token );
    //     sum += atof(token);
    //     token = strtok(NULL, " ");
    // }
    // fprintf(stderr, "Value is: %d\n", sum);
    return 0;
}