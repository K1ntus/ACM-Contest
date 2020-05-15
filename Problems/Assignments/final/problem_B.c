#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 

using namespace std;

#define __MODULO_OUTPUT__ 520
unsigned int findSolution(unsigned int x, unsigned int y);


int inverseTrue(int x, int y) {
    x = x % y;

    for(int i = 1; i < y; ++i) {
        if((i*x) % y == 1){
            return i;
        }
    }

    return -1;
}

int main () {
    fprintf(stderr, "Running Problem B...\n");

    string line;
    getline(cin, line);
    stringstream ss(line);
    int __nb_cases;
    ss>>__nb_cases;


    for(int case_id = 0; case_id < __nb_cases; ++case_id) {
        unsigned int y, n;
        getline(cin, line);
        stringstream tmp(line);
        tmp >> y >> n;

        // int mod_val = 520 % n;
        // fprintf(stderr,"Mod value: %d\n", mod_val);
        
        unsigned int gcd;
        // if(y < n ){
            gcd = findSolution(y,n);
        // } else {
        //     gcd = findSolution(y, y/n);
        // }

        // fprintf(stderr, "RES: %d\n",gcd);
        printf("%d\n", gcd);
    }



    return EXIT_SUCCESS;
}

unsigned int findSolution(unsigned int __y, unsigned int __modulo_value) {
    int left_side_value = __y / (__modulo_value % __y);
    fprintf(stderr, "Left: %d\n", left_side_value);
    for(int i = 1; i <= __modulo_value; i++){

        if((left_side_value * i) % __modulo_value == __MODULO_OUTPUT__) {
            return i;
        }
    }
    return-1;
}