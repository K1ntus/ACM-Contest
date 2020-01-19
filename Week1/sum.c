
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_VALUE 0
#define MAX_VALUE 1024

int main (void){




    // assert(argc >= 2);

    // FILE * f = fopen(args[1], "r");
    // //strtok better
    // char * buffer = (char*) malloc(sizeof(char) * 1024);
    // while(fgets(buffer, 1024, f) != 0x0){
        

    //     char left_buffer[1024];
    //     char right_buffer[1024];
        
    //     int pos = 0;
    //     while(buffer[pos] != ' ' && buffer[pos] != '\n'){
    //         left_buffer[pos] = buffer[pos];
    //         pos++;
    //     }

    //     while(buffer[pos] == ' ') 
    //         pos+=1;

    //     int i = 0;
    //     while(buffer[pos] != '\n' && buffer[pos] != 0x0){
    //         right_buffer[i] = buffer[pos];
    //         i++;
    //         pos++;
    //     }

    //     if(left_buffer == 0x0 || right_buffer == 0x0){
    //         continue;
    //     }
    //     int left_value = atoi(left_buffer);
    //     int right_value = atoi(right_buffer);



    //     // if(abs(left_value) > MAX_VALUE || abs(left_value) < MIN_VALUE){
    //     //     printf("Out of Range.\n");
    //     //     continue;
    //     // }
    //     // if(abs(right_value) > MAX_VALUE || abs(right_value) < MIN_VALUE){
    //     //     printf("Out of Range.\n");
    //     //     continue;
    //     // }
        
    char left[1024];
    char right[1024];
    while(scanf("%s %s", &left, &right) != EOF){
        int res_value = atoi(left) + atoi(right);
        
        printf("%d\n", res_value);

    }
    // free(buffer);
    // fclose(f);
    return EXIT_SUCCESS;
}