#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


typedef struct {
    char * name;
    int days_old;
} person;


/* Function to print an array */
void printArray(person *arr, int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("(%s,%d) ", arr[i].name, arr[i].days_old); 
    printf("\n"); 
} 
void swap(person *xp, person *yp) 
{ 
    person temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void BubbleSort(person *arr, int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j].days_old > arr[j+1].days_old) 
              swap(&arr[j], &arr[j+1]); 
} 


double convertDateToDays(int day, int month, int year) {
    int res = 0;

    res += day;
    res += (month * 30);
    res += (year * 365);

    return res;
}

int main (void) {
    int __nb_people__; 

    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_people__;

    person * person_array = (person *) malloc(sizeof(person) * __nb_people__);

    for(int people_number = 0; people_number < __nb_people__; people_number++){
        getline(cin, line);
        stringstream myString(line);

        char * n = (char *) malloc(sizeof(char) * 128);
        int d,m,y;

        myString >> n >> d >> m >> y;

        person current;
        current.name = n;
        current.days_old = convertDateToDays(d,m,y);
        //fprintf(stdout, "Added person: %s -> %d \n", n, current.days_old );
        person_array[people_number] = current;
    }

    BubbleSort(person_array, __nb_people__);
    //printArray(person_array, __nb_people__);
    fprintf(stdout, "%s\n", person_array[__nb_people__-1]);
    fprintf(stdout, "%s\n", person_array[0]);

    return EXIT_SUCCESS;
}