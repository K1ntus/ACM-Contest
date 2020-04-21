#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

// #define INT_MAX 2147483647



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

/*
int sizeBestTrend(int * trend_list, int size, int indice) {
    int max_value = trend_list[indice];
    int count = 1;

    for(int i = indice; i < size; i++) {
        int current_val = trend_list[i];
        // printf("Reading %d vs %d\n", current_val, max_value);
        if(current_val >= max_value) {
            max_value = current_val;
            count = count + 1;
        }
    }

    return count;
}
*/


int sizeBestTrend(int * trend_list, int size, int indice) {
    int max_len = 1;

    for(int j = 1; j < size; j++){
        int cur_len = 1;

        int min_val_subarr = trend_list[j];
        int max_id_subarr = j;

        // if(size-j-1 < max_len) break;

        for(int i = size - 1; i >= j; i--) {
            int value_l = trend_list[i-1];
            int value_r = trend_list[i];
            // printf("Reading %d vs %d\n", current_val, max_value);

            if(value_l == value_r) {
                max_id_subarr = i-1;
                min_val_subarr = trend_list[max_id_subarr];
                cur_len = cur_len + 1;
            }else if(value_l <= value_r) {
                cur_len = cur_len + 1;
            }else{
                if(i-1 >= j){
                }
            }
        }
        j = max_id_subarr;

        if(cur_len>max_len) max_len = cur_len;
        //if(cur_len >2) j = j + cur_len - 2;
    }

    return max_len;
}


int main (void) {
    string line;
    while(getline(cin, line)){
        stringstream myString(line);
        int __size_case__; 
        myString >> __size_case__;

        int * trend_array = (int*) malloc(sizeof(int) * __size_case__);
        // int * sorted_trend_array = (int*) malloc(sizeof(int) * __size_case__);
        getline(cin, line);
        stringstream trendString(line);
        for(int i = 0; i < __size_case__; i++) {
            int val;
            trendString >> val;
            trend_array[i] = val;
            // sorted_trend_array[i] = val;
            // printf("Saved trend value: %d\n", trend_array[i]);
        }
        
    //    / BubbleSort(sorted_trend_array, __size_case__);

        // int max_val = sorted_trend_array[__size_case__ / 2];
        int best_trend = 0;
        /*
        for(int i = 0; i < __size_case__; i++) {
            if (trend_array[i] < max_val){

                int val = sizeBestTrend(trend_array, __size_case__, i);
                

                if(val > best_trend){
                    best_trend = val;
                } 
            }
        }*/

        // printf("%d\n", best_trend);
        printf("%d\n", sizeBestTrend(trend_array, __size_case__, 0));

    }

}