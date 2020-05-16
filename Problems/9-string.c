#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


#define  __MAX_CHAR__ 25

#define __Z_INSTRUCTION_DELETE__ 'D'
#define __Z_INSTRUCTION_INSERT__ 'I'
#define __Z_INSTRUCTION_CHANGE__ 'C'
#define __Z_INSTRUCTION_ENDPRG__ 'E'

void processCharacter(char * current_str, int size_current_str, char * dest_str, int size_dest_str, int __position);
int getCharArraySize(char * array, int __max_size);
int GetOperationToUse(char * current_str, int size_current_str, char * dest_str, int size_dest_str);


int main (void) {
    char * left = (char *) malloc(sizeof(char) * __MAX_CHAR__);
    char * right = (char *) malloc(sizeof(char) * __MAX_CHAR__);

    for(int i = 0; i < __MAX_CHAR__; i++) {
        left[i] = right[i] = '\0';
    }

    while(!cin.eof()) {
        string line;
        getline(cin, line);
        stringstream input(line);

        input >> left >> right;
        if(left[0] == '#') { break; }

        int size_left = getCharArraySize(left, __MAX_CHAR__);
        int size_right = getCharArraySize(right, __MAX_CHAR__);


        // int res = GetOperationToUse(left, size_left, right, size_right);

        processCharacter(left, size_left, right, size_right, 0);
        printf("%c\n", __Z_INSTRUCTION_ENDPRG__);



        for(int i = 0; i < __MAX_CHAR__; i++) {
            left[i] = right[i] = '\0';
        }
    }

    return 0;
}















/**
 * 
 * Input processing Function
 * 
 * 
 */
enum {
    __DELETE__,
    __INSERT__,
    __CHANGE__,
    __NO_OPE__
};
void DeleteCharacterAtPosition(int __position, char * removed_char, char * input, int * size_input);
void InsertCharacterAtPosition(int __position, char __char_to_insert, char* input, int *size_input);
void UpdateCharacterAtPosition(int __position, char __new_char, char * input);
void PrintInstructionCode(int __instruction_type, char __charUpdated, int __position);

int min(int x, int y, int z) {
    return min(min(x,y),z);
}












// int GetOperationToUse(char * current_str, int size_current_str, char * dest_str, int size_dest_str) {
//     if(size_current_str == 0) { 
//         return size_dest_str;
//     }
    
//     if(size_dest_str == 0) {
//         return size_current_str;
//     }
    

//     if(dest_str[size_current_str - 1] == current_str[size_dest_str - 1]) {
//         return GetOperationToUse(current_str, size_current_str-1, dest_str, size_dest_str-1);
//     }

//     int res_insert = GetOperationToUse(current_str, size_current_str, dest_str, size_dest_str-1);
//     int res_remove = GetOperationToUse(current_str, size_current_str-1, dest_str, size_dest_str);
//     int res_update = GetOperationToUse(current_str, size_current_str-1, dest_str, size_dest_str-1);
//     int min_value = (min(res_insert, res_remove), res_update);
//     return 1 + min_value;

//     // if(current_str[__position] == dest_str[__position]) {           // Same character, nothing to do
//     //     return __NO_OPE__;
//     // } else if(__position + 1 < size_current_str) {                  // Not the end of input str
//     //     if(current_str[__position + 1] == dest_str[__position]){    // If next characteur from input is the character required
//     //         return __DELETE__;                                      // Delete current pos
//     //     } else {                                                    // Else change it
//     //         return __CHANGE__;
//     //     }
//     // } else if (__position == size_dest_str) {                       // Last Position and not same char
//     //     return __CHANGE__;                                          // Change it
//     // } else {
//     //     return __INSERT__;                                          // Insert the character
//     // }
// }
































/**
 * 
 * 
 *
 * 
 * BULLSHIT
 * 
 * 
 */




/**
 * Determine which operation to execute
 */
int GetOperationToUse(char * current_str, int size_current_str, char * dest_str, int size_dest_str, int __position) {
    if(current_str[__position] == dest_str[__position]) {           // Same character, nothing to do
        return __NO_OPE__;
    } else if (current_str[size_current_str] == dest_str[size_current_str]) {
        return __CHANGE__;
    } else if(__position + 1 < size_current_str) {                  // Not the end of input str
        if(current_str[__position + 1] == dest_str[__position]){    // If next characteur from input is the character required
            return __DELETE__;                                      // Delete current pos
        } else {                                                    // Else change it
            return __CHANGE__;
        }
    } else if (__position == size_dest_str) {                       // Last Position and not same char
        return __CHANGE__;                                          // Change it
    } else {
        return __INSERT__;                                          // Insert the character
    }
}

void processCharacter(char * current_str, int size_current_str, char * dest_str, int size_dest_str, int __position) {
    if(__position >= size_dest_str || strcmp(current_str, dest_str) == 0) {
        return;
    }
    
    int __operation_type = GetOperationToUse(current_str, size_current_str, dest_str, size_dest_str, __position);
    // int __operation_type = __NO_OPE__;
    char instruction_char;
    switch (__operation_type)    {
    case __INSERT__:
        instruction_char = dest_str[__position];
        InsertCharacterAtPosition(__position, instruction_char, current_str, &size_current_str);
        break;
    case __DELETE__:
        DeleteCharacterAtPosition(__position, &instruction_char, current_str, &size_current_str);
        break;
    case __CHANGE__:
        instruction_char = dest_str[__position];
        UpdateCharacterAtPosition(__position, instruction_char, current_str);
        break;
    
    default:
        break;
    }
    
    if(__operation_type != __NO_OPE__) {
        PrintInstructionCode(__operation_type, instruction_char, __position + 1);

    }
    processCharacter(current_str, size_current_str, dest_str, size_dest_str, __position + 1);
    return;

}


/**
 * 
 * Three Possible Operations
 * Insert/Delete/Update
 * 
 */
void DeleteCharacterAtPosition(int __position, char * removed_char, char * input, int * size_input) {
    *removed_char = input[__position];
    *size_input = *size_input - 1;
    for(int i = __position; i < *size_input; i++) {
        input[i] = input[i+1];
    }
    input[*size_input + 1] = '\0';
}


void InsertCharacterAtPosition(int __position, char __char_to_insert, char* input, int *size_input) {
    *size_input = *size_input + 1;
    for(int i = *size_input - 1; i >= __position; i--) {
        input[i] = input[i-1];
    }
    input[__position] = __char_to_insert;
}

void UpdateCharacterAtPosition(int __position, char __new_char, char * input){//, int __size_input) {
    input[__position] = __new_char;
}




/***
 * 
 * 
 * UTILS
 * 
 */


int getCharArraySize(char * array, int __max_size) {
    int sum = 0;
    for(int i = 0; i < __max_size; i++) {
        if(array[i] == '\0') { break; }
        sum = sum + 1;
    }
    return sum;
}


void PrintInstructionCode(int __instruction_type, char __charUpdated, int __position) {
    switch (__instruction_type) {
        case __DELETE__:
            printf("%c", __Z_INSTRUCTION_DELETE__);
            break;
        case __CHANGE__:
            printf("%c", __Z_INSTRUCTION_CHANGE__);
            break;
        case __INSERT__:
            printf("%c", __Z_INSTRUCTION_INSERT__);
            break;
        
        default:
            printf("Unknown Instruction: %d\n", __instruction_type);
            break;
    }

    printf("%c", __charUpdated);
    printf("%02d", __position);



}