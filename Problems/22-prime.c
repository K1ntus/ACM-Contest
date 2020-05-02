// C / C++ program for Dijkstra's shortest path algorithm for adjacency 
// list representation of graph 

// To Debug
// https://www.udebug.com/UVa/12101

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



// A structure to represent a stack 
struct Stack { 
    int top; 
    unsigned capacity; 
    int* array; 
}; 

int peek(struct Stack* stack);
int pop(struct Stack* stack);
void push(struct Stack* stack, int item);
int isEmpty(struct Stack* stack);
int isFull(struct Stack* stack);
struct Stack* createStack(unsigned capacity);

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

// p digit position
// x current value
// j new digit value
int UpdatePrimeValue(int x, int p, int j) {
    // printf("From: %d to", x);
    int a = x / p;
    int b = x % p;

    a = a - ((a%10) - j);

    int res = a * p + b;
    // printf(" %d\n", res);
    // res = res * digit_position + current_value % digit_position;

    return res;
}
/*
#define __FIRST_DIGIT__  0
#define __SECOND_DIGIT__ 1
#define __THIRD_DIGIT__  2
#define __FOUR_DIGIT__   3
int change(int n, int i, int j) {

    switch (i) {
        case __FIRST_DIGIT__:
            return ( (n / 10) * 10 + j );
        case __SECOND_DIGIT__:
            return ( (n / 100) * 100 + j * 10 + n % 10 );
        case __THIRD_DIGIT__:
            return ( (n / 1000) * 1000 + j * 100 + n % 100 );
        case __FOUR_DIGIT__:
            return ( j * 1000 + n % 1000 );
    }
}

*/



bool IsValidIntervalValue(int valueToTest) {
    if (valueToTest < 1000) {
        return false;
    }
    
    if (valueToTest > 9999) {
        return false;
    }

    return true;

}


int bfs(int startVertex, int destVertex, bool * prime_list) {
    if(!IsValidIntervalValue(startVertex) || !IsValidIntervalValue(destVertex) || prime_list[startVertex] || prime_list[destVertex]){
        return __NO_SOL__;
    }
    
    if(startVertex == destVertex) {
        return 0;
    }

    struct Stack* q = createStack(__SIZE__);

    bool * visited = (bool *) malloc(sizeof(bool) * __SIZE__);
    initArray(visited, __SIZE__);

    visited[startVertex] = true;
    push(q, startVertex);
    
    int depth = 1;
    
    while(!isEmpty(q)){

        for(int nb_ite_depth = q->top; nb_ite_depth >= 0; nb_ite_depth--) {    //Test every value from the current depth
            int currentVertex = pop(q);

            for(int digit_position = 0, offset = 1; digit_position < 4; digit_position++, offset*=10){
                for(int digit_value = 0; digit_value < 10; digit_value++) {
                    if(digit_position == 0 && digit_value == 0){ continue; }    //First digit and 0

                    int newValue = UpdatePrimeValue(currentVertex, offset, digit_value);

                    if(!IsValidIntervalValue(newValue) || visited[newValue]) {
                        continue;
                    }

                    if(!prime_list[newValue]) { 
                        if(newValue == destVertex) {
                            // if(depth == 1) {
                            //     return depth;
                            // } else {
                            //     return depth + 1;
                            // }
                            return depth + 1;
                        }

                        visited[newValue] = true;
                        push(q, newValue);
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


  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* createStack(unsigned capacity) 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (int*)malloc(stack->capacity * sizeof(int)); 
    return stack; 
} 
  
// Stack is full when top is equal to the last index 
int isFull(struct Stack* stack) 
{ 
    return stack->top == stack->capacity - 1; 
} 
  
// Stack is empty when top is equal to -1 
int isEmpty(struct Stack* stack) 
{ 
    return stack->top == -1; 
} 
  
// Function to add an item to stack.  It increases top by 1 
void push(struct Stack* stack, int item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    // printf("%d pushed to stack\n", item); 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
int pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top--]; 
} 
  
// Function to return the top from stack without removing it 
int peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return INT_MIN; 
    return stack->array[stack->top]; 
} 