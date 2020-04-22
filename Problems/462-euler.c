#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
//https://www.topcoder.com/community/competitive-programming/tutorials/prime-numbers-factorization-and-euler-function/



#define __MAX_VAL__ 100000000
bool IsPrime(int a) {
    int c;
   
    for (c = 2; c <= a - 1; c++) {
        if (a%c == 0)
            return false;
    }
    return true;
}


bool EvenNumberManager(int number) {
    int value = sqrt(number);

    return true;
}

bool * CreateNumberArray(){
    bool * array = (bool *) malloc (sizeof(bool) * __MAX_VAL__);

    for(int i = 0; i < __MAX_VAL__; i++){
        if(IsPrime(sqrt(i))) {
            array[i] = true;
        }
    }
    return array;
}

int fi(int n) {
int result = n;
for(int i=2;i*i <= n;i++) {
if (n % i == 0) result -= result / i;
while (n % i == 0) n /= i;
}
if (n > 1) result -= result / n;
return result;
}

bool* gen_primes(int max) {
    bool * primes = (bool *) malloc (sizeof(bool) * max);
    int i,j;
    for(i=0;i<max;i++) primes[i] = true;
    for(i=2;i<=(int)sqrt(max);i++)
        if (primes[i])
            for(j=i;j*i<max;j++) primes[i*j] = false;
    return primes;
}

void FindSol(int n, bool * primes) {
    int i;
    for(i=2;i<n;i++)
        if (primes[i] && primes[n-i]){
            printf("%d is the sum of %d and %d.", i, n-i);
            return;
        }
    printf("%d is not the sum of two primes!");
}

int main (void) {
    string line;
    // int * number_array = CreateNumberArray();
    int best_size = 1;
    while(getline(cin, line)) {
        int value;
        stringstream myString(line);
        myString >> value;
        bool* primes = gen_primes(value);
        // if(value > best_size){
        //     // free(primes);
        //     best_size = value;
        //     primes = gen_primes(best_size);
        // }
        //printf("res: %d\n", fi(value));
        
        FindSol(value, primes);
        printf("\n");
    }
}