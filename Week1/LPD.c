

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char isprime(long n);
int main(int argc, char * args[]) {


    FILE * f = fopen(args[1], "r");

    //strtok better
    char * buffer = (char*) malloc(sizeof(char) * 255);
    int overflow_prevent = 0;
    while(fgets(buffer, 1024, f) != 0 && overflow_prevent < 1000){
        overflow_prevent +=1;
        


    }

    fclose(f);
    free(buffer);
    return 0;
}



#define N 1000000
#define SQRT_N 1000
#define HALF_SQRT_N 500

long p[HALF_SQRT_N];
long count;

char isprime(long n)
{
	long i;

	if (n<4) 
		return 1;
	if ((n&1) == 0) 
		return 0; //even

	i=0;
	while(i < count) {
		if(n%(p[i]) == 0) 
			return 0;
		i++;
	}

	if((n-3)/2 < HALF_SQRT_N) 
		p[count++] = n;
	return 1;
}
