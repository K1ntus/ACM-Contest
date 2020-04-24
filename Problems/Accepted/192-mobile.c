#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


bool isMobileEquilibrium(int w_r, int d_r, int d_l, int w_l) {
    int right = w_r * d_r;
    int left = w_l * d_l;


    if(left == right)
        return true;
    // printf("Not Equilibrate: %d - %d\n", right, left);
    return false;
}





bool __isEquilibrium = true;

int recursionAddSubMobile() {
    string line;
    getline(cin, line);
    stringstream myString(line);
    int d_r, d_l, w_r, w_l;
    myString >> w_l >> d_l >> w_r >> d_r;

    if(w_l == 0) {
        w_l = recursionAddSubMobile();
    }

    if(w_r == 0) {
        w_r = recursionAddSubMobile();
    }

    __isEquilibrium = isMobileEquilibrium(w_r, d_r, d_l, w_l) && __isEquilibrium;
    return w_r + w_l;
}



int main (void) {
    int __nb_cases__; 

    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_cases__;
    getline(cin, line);

    for(int case_id = 0; case_id < __nb_cases__; case_id++){
        getline(cin, line);
        
        int size;


        // New case or end of analytic
        if(line.empty()){
            case_id = case_id - 1;
            __isEquilibrium = true;
            if(case_id < __nb_cases__) printf("\n");

            continue;
        }

        int d_r, d_l, w_r, w_l;
        stringstream myString(line);
        myString >> w_l >> d_l >> w_r >> d_r;


        if(w_l == 0) {
            w_l = recursionAddSubMobile();
        }
        
        if(w_r == 0) {
            w_r = recursionAddSubMobile();
        }

        if(__isEquilibrium  && isMobileEquilibrium(w_r, d_r, d_l, w_l) ){
            printf("YES\n");
        } else {
            printf("NO\n");
        }

    }


    return EXIT_SUCCESS;
}