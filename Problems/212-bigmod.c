// https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/modular-exponentiation



#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __OFFSET__ 8

int applyMod(int x, int y, int mod_val) {
    int res = 1;

    while(y > 0) {
        if(y > __OFFSET__) {
            res *= (((int)pow(x, __OFFSET__)) % mod_val);
            y -= __OFFSET__;
        } else {
            res *= (((int)pow(x, y)) % mod_val);
            y = 0;
        }

        // printf("--- current res: %d || %d ^ %d mod %d\n", res, x, y, mod_val);
    }


    return res;
}


int main (void) {
    string line;

    while(!cin.eof()) {
        int x, y, mod_val;

        getline(cin, line);
        stringstream string_x(line);
        getline(cin, line);
        stringstream string_y(line);
        getline(cin, line);
        stringstream string_mod(line);


        string_x >> x;
        string_y >> y;
        string_mod >> mod_val;

        printf("Number: %d^%d mod %d\n", x, y, mod_val);


        int sum_mod = applyMod(x, y, mod_val);

        printf("Sum of mod: %d\n", sum_mod);

        int res = sum_mod % mod_val;

        printf("Res: %d\n", res);
        
        getline(cin, line);
    }


    return EXIT_SUCCESS;
}