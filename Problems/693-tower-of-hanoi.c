#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


int tower(int no,char a,char b,char c, int nb_steps);

// int main() {
//     int no;
//     printf("Enter total number of disks:");
//     scanf("%d",&no);
//     int res = tower(no,'A','B','C', 0);

//     printf("%d move required\n");
//     return 0;
// }


int main (void) {
    int __nb_disks; 

    string line;

    while(!cin.eof()){
        getline(cin, line);
        stringstream myString(line);
        myString >> __nb_disks;


        int res = tower(__nb_disks, 'A','B','C',0);
        printf("%d move required\n", res);

        getline(cin, line);

    }


    return EXIT_SUCCESS;
}



int tower(int no,char a,char b,char c, int nb_steps) {
    int res = 0;
    if(no>0) {
        res += tower(no-1,a,c,b, nb_steps + 1);
        printf("%c->%c\n",a,c);
        res += tower(no-1,b,a,c, nb_steps + 1);
    } else if (no == 0) {
        // tower(no, )
    }

    return nb_steps;
}