#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;







int main (void) {
    int __nb_case__; 

    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_case__;


    for(int case_id = 0; case_id < __nb_case__; case_id++){
        getline(cin, line);
        stringstream myString(line);
        
        int nb_people;
        myString >> nb_people;
        // if(nb_people == 2) printf("2\n");
        // else if (nb_people == 1) printf("1\n");
        // else printf("%d\n", nb_people - 2);
        int res = 0;
        if(nb_people == 1) {
            res = 0;
        } else {
            res = nb_people - 2;
        }
        
        printf("%d\n", res);

        // }
        // printf("%d\n", nb_people / 2);
        // if(nb_people % 2 == 0){
        //     printf("0\n");
        // }else{
        //     printf("1\n");
        // }
        
    }


    return EXIT_SUCCESS;
}