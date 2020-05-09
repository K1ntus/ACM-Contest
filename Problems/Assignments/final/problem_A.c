#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 



void GiveCandies(int *human, int*candy_type) {
    // printf("%d c/andies available. Require:%d\n", *candy_type, *human);
    if(*candy_type > *human) {
        *candy_type = *candy_type - *human;
        *human = 0;
    } else {
        *human = *human - *candy_type;
        *candy_type = 0;
    }
}

void HappiestDistribution(int alice, int eugeo, int kirito) {

    if(alice <= 0 && eugeo <= 0 && kirito <= 0){
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main () {
    int __number_of_cases__;

    scanf("%d", &__number_of_cases__);

    for(int case_id = 0; case_id < __number_of_cases__; case_id++) {
        int candies_for_kirito, candies_for_eugeo, candies_for_alice;
        int nb_black_candies, nb_blue_candies, nb_yellow_candies;

        scanf("%d", &candies_for_kirito);
        scanf("%d", &candies_for_eugeo);
        scanf("%d", &candies_for_alice);


        scanf("%d", &nb_black_candies);
        scanf("%d", &nb_blue_candies);
        scanf("%d", &nb_yellow_candies);



        GiveCandies(&candies_for_kirito, &nb_black_candies);

        GiveCandies(&candies_for_eugeo, &nb_black_candies);
        GiveCandies(&candies_for_eugeo, &nb_blue_candies);


        GiveCandies(&candies_for_alice, &nb_yellow_candies);
        GiveCandies(&candies_for_alice, &nb_black_candies);
        GiveCandies(&candies_for_alice, &nb_blue_candies);

        HappiestDistribution(candies_for_alice, candies_for_eugeo, candies_for_kirito);
    }
}