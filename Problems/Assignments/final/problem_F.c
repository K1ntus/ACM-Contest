#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 


#define __NUMBER_RABBITS__ 10

#define ASC_ORDER 0
#define DESC_ORDER 1

/* Function to print an array */
void printArray(int *arr, int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

bool IsArrayOrdered(int* array) {
    int order_type=-1;
    if(array[0] > array[1]){
        order_type = DESC_ORDER;
    } else {
        order_type = ASC_ORDER;
    }

    for(int i = 0; i < __NUMBER_RABBITS__-1; i++){
        // printf("Rabbit1(%d), Rabbit2(%d)\n", array[i], array[i+1]);
        if(order_type == DESC_ORDER){
            if(array[i] < array[i+1]) return false;
        } else {
            if(array[i] > array[i+1]) return false;
        }
    }

    return true;
}
  

int main () {
    int __number_of_cases__;

    scanf("%d", &__number_of_cases__);
    printf("Rabbits:\n");

    for(int case_id = 0; case_id < __number_of_cases__; case_id++) {
        int * rabbit_array = (int *) malloc(sizeof(int) * __NUMBER_RABBITS__);
        for(int i = 0; i < __NUMBER_RABBITS__; i++){
            scanf("%d", &rabbit_array[i]);
        }

        // printf("Rabbit Array:\n");
        // printArray(rabbit_array, __NUMBER_RABBITS__);
        
        // printf("ORDERED:\n");
        if(IsArrayOrdered(rabbit_array))
            printf("Ordered\n");
        else
            printf("Unordered\n");
    }
}