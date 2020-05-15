#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 

using namespace std;

void GenerateAllPossiblePatterns(char * left, char * right, int __size_str, int __minimal_pattern_size){
    
    int __max_nb_patterns = 0;
    for(int i = __size_str; i >=0 && i > __minimal_pattern_size; i--) {
        __max_nb_patterns += (__size_str / i) * i;
    }

    // char ** patterns_table = (char ** ) malloc(sizeof(char*) * __max_nb_patterns);
    // fprintf(stderr, "Max nb patterns possible: %d\n", __max_nb_patterns);

    // for(int i = 0; i < __max_nb_patterns; i++) {
    //     patterns_table[i] = malloc(sizeof(char) * __size_str);
        
    // }
}

int main () {
    fprintf(stderr, "Running Problem D...\n");


    string line;
    getline(cin, line);
    stringstream nb_c(line);

    int __nb_cases;
    nb_c >> __nb_cases;

    for(int case_id = 0; case_id < __nb_cases; case_id++) {
        int __minimal_size;
        char * left  = (char *) malloc(sizeof(char) * 1000);
        char * right = (char *) malloc(sizeof(char) * 1000);
        int __size_input;

        getline(cin, line);
        stringstream input_1(line);
        input_1 >> left;
        getline(cin, line);
        stringstream input_2(line);
        input_2 >> right;
        getline(cin, line);
        stringstream input_3(line);
        input_3 >> __minimal_size;

        __size_input = strlen(left);

        GenerateAllPossiblePatterns(left, right, __size_input, __minimal_size);

    }

    return EXIT_SUCCESS;
}