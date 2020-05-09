#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 



void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void BubbleSort(int *arr, int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

/* Function to print an array */
void printArray(int *arr, int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  

void MergeClassmates(int* classmate_arrays, int classmate_array_size, int* group_output) {

    for(int classmate_id = 0; classmate_id < classmate_array_size/2; classmate_id++){
        group_output[classmate_id] = classmate_arrays[classmate_id] + classmate_arrays[classmate_array_size - classmate_id -1];
    }
}



// Driver code 
int main(void){  
    char * buffer_size_class = (char *) malloc(sizeof(char) * 50);


    while(fgets(buffer_size_class, 50, stdin)){
        int size_class = atoi(buffer_size_class);
        if(size_class < 1 || size_class > 50) { continue; }
        // printf("Classroom of size: %d\n", size_class);

        int* class_knowledge_level = (int*) malloc(sizeof(int) * size_class);
        int size_array = 0;

        for(int i = 0; i < size_class; i++){
            int student_level;
            scanf("%d", &student_level);
            class_knowledge_level[i] = student_level;
        }

        BubbleSort(class_knowledge_level, size_class);
        // printf("Sorted Array:\n");
        // printArray(class_knowledge_level, size_class);


        int * groups = (int *) malloc(sizeof(int) * (size_class/2));
        MergeClassmates(class_knowledge_level, size_class, groups);
        BubbleSort(groups, size_class/2);

        // printf("Groups Knowledge:\n");
        // printArray(groups, size_class/2);

        // printf("Maximum ecarts:\n");
        printf("%d\n", groups[size_class/2 -1] - groups[0]);
    }
    return 0;  
}  
  
// This code is contributed by rathbhupendra 
