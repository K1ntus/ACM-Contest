
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
#include <stddef.h>


using namespace std;

#define __MAX_CHAR__ 100
#define __MAX_ELEMS__ 10
#define __MIN_ELEMS__ 1

#define __PRECISION__ 0.00001

#define __OFFSET__ 10000.0
#define __ZERO__ 0.000000

// A structure to represent a stack 
struct Stack { 
    int top; 
    unsigned capacity; 
    double* array; 
}; 

double peek(struct Stack* stack);
double pop(struct Stack* stack);
void push(struct Stack* stack, double item);
int isEmpty(struct Stack* stack);
int isFull(struct Stack* stack);
struct Stack* createStack(unsigned capacity);

double RoundValue(double input) {

    double output = input;
    int tmp_buffer = 0;
    // printf("Input to round: %f\n", input);
    input = input * __OFFSET__;
    tmp_buffer = (int) floor(input);
    // printf("-- I1:%d\n-- I2:%f\n", tmp_buffer, input);
    // input = input - tmp_buffer;
    // printf("---- Ires:%f\n", input);

    if(input > 0.0 && input < 0.0001) {
        // tmp_buffer += 1;
    } else if (input < 0.0) {
        // tmp_buffer -= 1;
    } else {
        tmp_buffer = ceil(input);

    }
    // printf("-- tmp value:%f\n", tmp_buffer);
    output = (double) (tmp_buffer / __OFFSET__);
    // printf("Output rounded: %f\n", output);

    return output;
}


int main(void) {

    string line;
    bool consecutive_case = false;

    while(!cin.eof()) {
        getline(cin, line);
        line.append(" 0");
        stringstream myString(line);
        // myString  << " 0";
        struct Stack * stack = createStack(__MAX_ELEMS__);

        if(consecutive_case) {
            printf("\n");
        } else {
            consecutive_case = true;
        }


        double tmp;
        for(int i = 0; i < __MAX_ELEMS__; ++i){
            myString >> tmp;
            push(stack, tmp);
        } 

        // while(myString >> tmp) {
            // fprintf(stderr, "aa\n");
            // push(stack, tmp);
        // }


        double res = 0;
        while(!isEmpty(stack)) {
            double tmp = pop(stack);
            // fprintf(stderr, "poped:%f\n", tmp);
            res += tmp;
        }


        // fprintf(stderr, "");
        res = RoundValue(res);
        printf("%0.4f\n",res);
    }

}









/*
bool fgreater(long double a, long double b) {
    return fabs(fabs(a)-fabs(b)) > __PRECISION__;
}


long double RoundsValue(long double result){
    long double saving_result = result * 10000.0;
    // if(saving_result > 0)
        saving_result = floor(saving_result);
    // else
    //     saving_result = ceil(saving_result);
    saving_result = trunc(saving_result);
    long double tmp_result = result * 10000.0;
    if (fgreater(tmp_result, saving_result)){
        // printf("Result is: %Lf, other one is: %Lf\n", tmp_result, saving_result);
        saving_result += 1;
    } 
    result = saving_result / 10000.0; 

    return result;
}

int main (void){
    char tmp_buffer[MAX_CHAR];
    long double result = 0.0;

    char *eof_checker;
    int consecutive_case = 0;

    while(eof_checker = fgets(tmp_buffer, MAX_CHAR, stdin)) {
        if(!eof_checker) break;
        else if(!strcmp(tmp_buffer, "\n")) continue;
        else if(eof_checker[0] == EOF) break;
        else
            if(consecutive_case > 0) printf("\n");// && tmp_buffer[0] != EOF) printf("\n");
            else consecutive_case = 1;

        char * buffer = (char *) malloc(MAX_CHAR * sizeof(char));
        strcpy(buffer, tmp_buffer);

        for(int j = 0; j < MAX_ELEMS; j++){
            if(buffer[0] == '\n') break;
            // result += strtold(buffer, &buffer);
            result += strtod(buffer, &buffer);
            // printf("Value is : %Lf\n", result);
        }

            // printf("Final Value is : %.4Lf\n", result);
        fprintf(stdout, "%.4Lf\n", RoundsValue(result));// (long double) ((long int) floorl( 10000*(result))) / 10000);

        result = 0.0;


        
        // char * tok = strtok(buffer, " ");
        
        // int j = 0;
        // while (tok != NULL && tok != "\n" && j < MAX_ELEMS) {
        //     if(tok != 0x0)
        //         result += strtold(tok, NULL);
        //     tok = strtok (NULL, " ");
        //     j++;
        // }
        
        // result *= 10000;
        // printf("previous result:%Lf\n", result);
        
        // long double final_result = floor(result * 10000.0)/10000.0;
        // if(final_result < result){

        //     printf("Current result: %Lf\nRounded result: %Lf\n", final_result, result);
        //     final_result += 0.0001;
        // }
        // // printf("%Lf->", result);
        // long double tmp_result = floorl(result);
        // if (tmp_result < result) {
        //     tmp_result+=1;
        // }
        // result = tmp_result;
        // result = truncl(result);
        // // printf("%Lf->", result);
        // result = result / 10000.0;
        // // result /= 10000;
        // char res_buffer[1024];
        // sprintf(res_buffer, "%Lf\n", final_result);
        // int i = 0;
        // while(res_buffer[i] != '.' && i < 10){
        //     printf("%c", res_buffer[i]);
        //     i+=1;
        // }
        
        // for(; i < 4; i++) {
        //     printf("%c", res_buffer[i]);
        // }
        // printf("\n");
        // // std::cout.unsetf ( std::ios::floatfield );                // floatfield not set
        // // std::cout.precision(4);
        // // std::cout << final_result << '\n';

        // std::cout.unsetf ( std::ios::floatfield );  
        // cout.precision(4);
        // double tmp = dround(result,4);
        // // if(result - tmp >0) tmp += 0.0001;
        // cout << fixed << tmp << endl;
        // long long tmp_result = ( (long long) (ceil(result * 10000)));
        // tmp_result = trunc(tmp_result);
        // // if(tmp_result < result) tmp_result += 0.0001;
        // result =(long double) (tmp_result / 10000.0);
        // std::cout << prd(result,4) << std::endl;
        // truncl(result);
        // // result = result / 10000.0;
        // double dround(double val, int dp)
        // fprintf(stdout, "%.4Lf\n", result);// (long double) ((long int) floorl( 10000*(result))) / 10000);
        result = 0.0;

        // free(tok);
        // free(buffer);
    }
    
    return EXIT_SUCCESS;
}
*/









  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* createStack(unsigned capacity) 
{ 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (double*)malloc(stack->capacity * sizeof(double)); 
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
void push(struct Stack* stack, double item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    // printf("%d pushed to stack\n", item); 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
double pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return DBL_MIN; 
    return stack->array[stack->top--]; 
} 
  
// Function to return the top from stack without removing it 
double peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return DBL_MIN; 
    return stack->array[stack->top]; 
} 