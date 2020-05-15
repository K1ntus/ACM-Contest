#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 

using namespace std;

double tick(double* distance, double __speed_left, double __speed_right, double __speed_corgi) {
    double __sum_speed = __speed_right + __speed_left;
    // fprintf(stderr, "Sum speed: %d || Distance: %d\n", __sum_speed, *distance);
    if(__sum_speed >= *distance) {
        return 0;
    }

    int res = 0;
    while(*distance > __sum_speed){
        *distance = *distance - __sum_speed;
        res += 1;
    }

    return res;
}



int main () {
    fprintf(stderr, "Running Problem A...\n");

    while(!cin.eof()) {
        double remaining_distance, speed_sir, speed_miss, speed_corgi;

        string line;
        getline(cin, line);
        if(line.empty() || line.size() == 0) { continue; }
        stringstream input_ss(line);
        input_ss >> remaining_distance >> speed_sir >> speed_miss >> speed_corgi;



        int nb_full_tick = tick(&remaining_distance, speed_sir, speed_miss, speed_corgi);

        double distance_for_corgi = speed_corgi * nb_full_tick;
        distance_for_corgi += (speed_corgi * ( (double)remaining_distance / (speed_miss + speed_sir)));

        if(distance_for_corgi == floor(distance_for_corgi)) {
            printf("%d\n", (int) distance_for_corgi);
        } else {
            printf("%.04f\n", distance_for_corgi);
        }
    
    }
    return EXIT_SUCCESS;
}