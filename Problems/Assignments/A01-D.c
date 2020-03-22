// C / C++ program for Dijkstra's shortest path algorithm for adjacency 
// list representation of graph 

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h>

int g(int n);
int f(int n);

int main(void) { 
    int nb_queries;
    scanf("%d", &nb_queries);


    for(int query = 0; query < nb_queries; query++) {
        int l, r, k;

        scanf("%d", &l);
        scanf("%d", &r);
        scanf("%d", &k);

        int sum = 0;

        for(int i = l;i <= r; i++) {
            if(g(i) == k) {
                sum += 1;
            }

        }
        fprintf(stdout, "%d\n", sum);
    }

    return EXIT_SUCCESS;
}


int f(int n) {
    int res = 0;
    while(n) {
        res += n%10;
        n /= 10;
    }
    return res;
}

int g(int n) {
    if (n >= 10){
        return g(f(n));
    }
    return n;  
}

