// C / C++ program for Dijkstra's shortest path algorithm for adjacency 
// list representation of graph 

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h>
#include <string.h>
#include <bits/stdc++.h> 
using namespace std; 

//Number of prime numbers between 1000 and 9999
#define __SIZE__ 10010
#define __NO_SOL__ -1



struct Queue {
    int items[__SIZE__];
    int front;
    int rear;
};

struct Queue* createQueue();
void enQueue(struct Queue* q, int);
int deQueue(struct Queue* q);
void display(struct Queue* q);
int isEmpty(struct Queue* q);
void printQueue(struct Queue* q);

struct node
{
    int vertex;
    struct node* next;
};


int bfs(int startVertex, int destVertex, bool * prime_list);


// Source: https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/

bool primes[10000];
// void gen_primes(int max) {
//     bool * primes = (bool *) malloc (sizeof(bool) * max);
//     int i,j;
//     for(i=0;i<max;i++) primes[i] = true;
//     for(i=2;i<=(int)sqrt(max);i++)
//         if (primes[i])
//             for(j=i;j*i<max;j++) primes[i*j] = false;
//     return primes;
// }

void initArray(bool * array, int size) {
    for(int i = 0; i < size; i++){
        array[i] = false;
    }
}

void siv() {
    initArray(primes, __SIZE__);
    // for(int i =0; i < __SIZE__; i++) { primes[i] = false;}
	for (int i = 2; i * i <= __SIZE__; ++i) {
		if (!primes[i])
			for (int j = i * i; j <= __SIZE__; j += i)
				primes[j] = true;
	}

}

int main() { 
    // bool * prime_table = gen_primes(10000);
    siv();
    int V; // Number of cities/Vertices
    int E; // Number of connections/Edges in graph  
    string line;
    getline(cin, line);
    stringstream myString(line);

    int __nb_case__ = 0;
    myString >> __nb_case__;

    for(int case_id = 0; case_id < __nb_case__; case_id++) {
        
        // getline(cin, line); //Empty Line

        getline(cin, line);
        stringstream myString(line);

        int src, dest;
        myString >> src >> dest;

        int res;
        if((res = bfs(src, dest, primes)) == __NO_SOL__) {
            printf("Impossible\n");
        } else {
            printf("%d\n", res);
        }

    }
	return 0; 
} 





































/**
 *     This is a simple BFS problem . There is nothing special to mention for this problem.

    1.  First generate prime number upto  9999.

    2.  Then just run BFS from the initial number. Like if the number is 1033 where else we can go

    2.a  Changing the first digit we get 8 number (2-9)033, changing second digit we get 9 number 1(1-9)33 and so  on.  If   any of the number is prime then place it in queue and mark this as visited so that you don’t push it again.

    3.  Push and Pop the numbers until you get the desired number. If number not found print “Impossible.” else print the distance.

**/

int UpdateValue(int x, int p, int j) {
    // printf("From: %d to", x);
    int a = x / p;
    int b = x % p;

    a = a - ((a%10) - j);

    int res = a * p + b;
    // printf(" %d\n", res);
    // res = res * digit_position + current_value % digit_position;

    return res;
}

bool IsValidValue(int valueToTest) {
    if (valueToTest < 1000) {
        return false;
    }
    
    if (valueToTest > 9999) {
        return false;
    }

    return true;

}


int bfs(int startVertex, int destVertex, bool * prime_list) {
    if(!IsValidValue(startVertex) || !IsValidValue(destVertex) || prime_list[startVertex] || prime_list[destVertex]){
        return __NO_SOL__;
    }
    
    if(startVertex == destVertex) {
        return 0;
    }

    struct Queue* q = createQueue();

    bool * visited = (bool *) malloc(sizeof(bool) * __SIZE__);
    initArray(visited, __SIZE__);

    visited[startVertex] = true;
    enQueue(q, startVertex);
    
    int depth = 1;
    
    while(!isEmpty(q)){

        for(int nb_ite_depth = q->rear + 1; nb_ite_depth > 0; nb_ite_depth--) {    //Test every value from the current depth
            int currentVertex = deQueue(q);

            for(int digit_position = 0, offset = 1; digit_position < 4; digit_position++, offset*=10){

                for(int digit_value = 0; digit_value < 10; digit_value++) {
                    if(digit_position == 0 && digit_value == 0){ continue; }    //First digit and 0

                    int newValue = UpdateValue(currentVertex, offset, digit_value);

                    if(!IsValidValue(newValue) || visited[newValue]) {
                        continue;
                    }

                    if(!prime_list[newValue]) { 
                        if(newValue == destVertex) {
                            if(depth == 1) {
                                return depth;
                            } else {
                                return depth + 1;
                            }
                            // return depth + 1;
                        }

                        visited[newValue] = true;
                        enQueue(q, newValue);
                    }

                }   //End digits replacement

                // offset *= 10;
            }
        }

        depth = depth + 1;
        // printf("Adding a depth.\n");
    }

    return __NO_SOL__;
}




struct Queue* createQueue() {
    struct Queue* q = (struct Queue *) malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}


int isEmpty(struct Queue* q) {
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void enQueue(struct Queue* q, int value){
    if(q->rear == __SIZE__-1){
        // printf("\nQueue is Full!!");
     } else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int deQueue(struct Queue* q){
    int item;
    if(isEmpty(q)){
        // printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear) {
            // printf("Resetting Queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct Queue *q) {
    int i = q->front;

    if(isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }
    }    
}