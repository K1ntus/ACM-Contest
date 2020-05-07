#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


int CreateNewBox(int __max_sections, int * nb_divisors_available) {
    int nb_sections = 1;

    if(*nb_divisors_available <= __max_sections - 1) {
        nb_sections += *nb_divisors_available;
        *nb_divisors_available = 0;
    } else {
    // } else if (*nb_divisors_available >= __max_sections) {
        nb_sections = __max_sections;
        *nb_divisors_available -= (__max_sections - 1);
    }
    return nb_sections;
}

int GetAvailableSpaceBox(int __nb_sections, int __section_capacity) {
    int __to_fill = __nb_sections * __section_capacity;
    // printf("---- Filled %d sections with %d nuts\n", __nb_sections, __to_fill);
    return __to_fill;
}

int main (void) {
    int __nb_people__; 

    while(!cin.eof()) {
        string line;
        getline(cin, line);
        stringstream myString(line);


        int max_nb_sections, nb_nuts, nb_divisors, section_capacity;

        myString >> max_nb_sections >> nb_nuts >> nb_divisors >> section_capacity;
        

        unsigned int __nb_boxes = 0;
        while(nb_nuts > 0) {
            int new_box_sections = 1;
            if(nb_divisors > 0) {
                new_box_sections = CreateNewBox(max_nb_sections, &nb_divisors);
                // fprintf(stdout, "--- Box with %d sections created.\n", new_box_sections);
            }

            nb_nuts = nb_nuts - GetAvailableSpaceBox(new_box_sections, section_capacity);

            __nb_boxes = __nb_boxes + 1;
            
        }

        // printf("%d boxes required.\n", __nb_boxes);
        printf("%d\n", __nb_boxes);
    }


    return EXIT_SUCCESS;
}