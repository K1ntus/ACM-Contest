#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __SIZE_INPUT_STRING__ 100000
#define __SIZE_OUTPT_STRING__ 200000



bool isPalindrome(char * __array, int __size_array, int*output_pos);
int getCharArraySize(char * array, int __max_size);
int getPosLongestPalindromeSuffix(char * __array, int __size_array);


int main (void) {
    while(!cin.eof()) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        char * input_array = (char*) malloc(sizeof(char) * __SIZE_INPUT_STRING__);
        ss >> input_array;
        int __size_input = getCharArraySize(input_array, __SIZE_INPUT_STRING__);

        int pos_not_palindrome = - 1;
        if(isPalindrome(input_array, __size_input, &pos_not_palindrome)) {
            printf("%s\n", input_array);
            continue;
        } else {
            // printf("Word [%s] NOT a palindrome from indice %d:\n", input_array, pos_not_palindrome);
            printf("%s", input_array);
        }

        pos_not_palindrome = getPosLongestPalindromeSuffix(input_array, __size_input);

        if(pos_not_palindrome == -1) {  // No palindrome suffix
            for(int i = __size_input - 2; i >= 0; --i) {
                printf("%c", input_array[i]);
            }
        } else {
            for(int i = pos_not_palindrome - 1; i >= 0; --i) {
                printf("%c", input_array[i]);
            }
        }

        printf("\n");
        free(input_array);

    }


}


int getCharArraySize(char * array, int __max_size) {
    int sum = 0;
    for(int i = 0; i < __max_size; i++) {
        if(array[i] == '\0') { break; }
        sum = sum + 1;
    }
    return sum;
}

bool isPalindrome(char * __array, int __size_array, int* output_pos) {

    int __middle_position = __size_array / 2;// + __size_array % 2;
    // printf("-- Middle: %d\n", __middle_position);

    for(int i = __middle_position; i >= 0; --i) {
        if(__array[i] != __array[__size_array - i - 1]) {
            *output_pos = i;
            return false;
        }
    }
    return true;
}


// // A function to check if a string str is palindrome 
// void isPalindrome(char str[]) { 
//     // Start from leftmost and rightmost corners of str 
//     int l = 0; 
//     int h = strlen(str) - 1; 
//     
//     // Keep comparing characters while they are same 
//     while (h > l) { 
//         if (str[l++] != str[h--]) { 
//             printf("%s is Not Palindrome", str); 
//             return; 
//         } 
//     } 
//     printf("%s is palindrome", str); 
// } 



int getPosLongestPalindromeSuffix(char * __array, int __size_array) {
    int best_pos = -1;
    for(int i = __size_array; i >= __size_array / 2 - 1 ; i--) {
        int output_pos = 0;

        // printf("--- Testing : %s.\n", __array + i);
        if(isPalindrome(__array + i, __size_array - i, &output_pos)) {
            // printf("Find a palindrome at pos %d\n", i);

            int pos = (__size_array - i);
            // printf("Find a palindrome at pos2 %d\n", pos);

            // if(!isPalindrome(__array + i + 1, __size_array - i + 1, &output_pos)) {
            // printf("Find a non palindrome at pos %d\n", output_pos  + i);
                if(2*pos >= __size_array) {    //Suffix
                    best_pos = pos - 3;
                }

            // }

        }
    }

    return best_pos;
}

