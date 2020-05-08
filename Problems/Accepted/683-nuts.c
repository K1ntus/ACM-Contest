#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

// I know that the norm required to create function using camel-case, really sorry I like it
// Like that these days, and it is not really a "big" project ahah *-*
int GetAvailableSpaceBox(int __nb_sections, int __section_capacity);
int CreateNewBox(int __max_sections, int * nb_divisors_available);




int main (void) {
    int __nb_people__; 

    while(!cin.eof()) {
        string line;
        getline(cin, line);
        stringstream myString(line);

        if(line.size() < 4) {
            continue;
        }

        int max_nb_sections, nb_nuts, nb_divisors, section_capacity;

        myString >> max_nb_sections >> nb_nuts >> nb_divisors >> section_capacity;
        

        unsigned int __nb_boxes = 0;
        while(nb_nuts > 0) {
            int new_box_sections = 1;

            // If we still have at least one additional divisors, update box sections nb
            if(nb_divisors > 0) {
                new_box_sections = CreateNewBox(max_nb_sections, &nb_divisors);
            }

            // Nb nuts minus the nb_section of a box * capacity per section
            nb_nuts -= GetAvailableSpaceBox(new_box_sections, section_capacity);

            // Increment box counter
            __nb_boxes = __nb_boxes + 1;
            
        }

        printf("%d\n", __nb_boxes);
    }


    return EXIT_SUCCESS;
}



int CreateNewBox(int __max_sections, int * nb_divisors_available) {
    int nb_sections = 0;

    if(*nb_divisors_available < __max_sections - 1) {
        nb_sections += *nb_divisors_available;
        *nb_divisors_available = 0;
    } else {
        nb_sections += __max_sections - 1;
        *nb_divisors_available -= (__max_sections - 1);
    }

    return nb_sections + 1;
}

int GetAvailableSpaceBox(int __nb_sections, int __section_capacity) {
    return __nb_sections * __section_capacity;
}
