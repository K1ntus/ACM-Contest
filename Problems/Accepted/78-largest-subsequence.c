#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __MAX_LENGTH__ 52


char * getBestString(char* input_str, int size_str);

int main (void){

    string line;
    getline(cin, line);
    int __number_of_tests__;
    stringstream testString(line);
    testString >> __number_of_tests__;

    for(int case_id = 0; case_id < __number_of_tests__; ++case_id) {
        char * word_to_analyze = (char *) malloc(sizeof(char) * __MAX_LENGTH__);
        getline(cin, line);
        stringstream wordstream(line);
        wordstream >> word_to_analyze;

        char * res = getBestString(word_to_analyze, line.size());
        printf("%s\n", res);


    }

    return 0;
}


char * getBestString(char* input_str, int size_str) {
    if(size_str <= 1) {
        return input_str;
    } else {
        char * tmp_str; // = (char *) malloc(sizeof(char) * size_str);
        tmp_str = (input_str + sizeof(char));   //Oh damn I love pointer arithmetic ahahah
        
        // for(int i = 1; i < size_str; ++i) {
        //     tmp_str[i-1] = input_str[i];
        // }
        // tmp_str[size_str - 1] = '\0';

        tmp_str = getBestString(tmp_str, size_str - 1);

        if(tmp_str[0] <= input_str[0]) {
            char * res = (char *) malloc(sizeof(char) * __MAX_LENGTH__);
            res[0] = input_str[0];
            strcat(res, tmp_str);

            return res;
        }
        return tmp_str;
    }
}

