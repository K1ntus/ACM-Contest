
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
#include <stddef.h>


using namespace std;

#define __MAX_LINES__ 50
#define __PRECEDENCE_HIGH__ 2
#define __PRECEDENCE_LOW__  1
#define __PRECEDENCE_UNKN__ 0

// A structure to represent a stack 
struct Stack { 
    int top; 
    unsigned capacity; 
    char* array; 
}; 

char peek(struct Stack* stack);
char pop(struct Stack* stack);
void push(struct Stack* stack, char item);
int isEmpty(struct Stack* stack);
int isFull(struct Stack* stack);
struct Stack* createStack(unsigned capacity);



void updatePostfixEquation(char*eq, int * pos, char val);
void readInput(char * array);

bool isOperator(char c);
bool isDigit(char c);
int getPredecence(char c);
void printPostfixEquation(char * stack_postfix);

int main (void) {
    int __nb_case__ = 0;

    string line;
    getline(cin, line);
    stringstream nbCasesString(line);

    nbCasesString >> __nb_case__;


    getline(cin, line); //Removing empty line
    for(int case_id = 0; case_id < __nb_case__ && !cin.eof(); case_id++) {
        char infix_equation[__MAX_LINES__ + 2];
        char postix_equation[__MAX_LINES__];


        Stack * stack = createStack(__MAX_LINES__);
        push(stack, '(');

        readInput(infix_equation);



        int infix_eq_position = 0;
        int postfix_eq_position = 0;
        char current_char;
        while((current_char = infix_equation[infix_eq_position]) != '\0' && infix_eq_position < __MAX_LINES__) {

            if(isDigit(current_char)) {
                updatePostfixEquation(postix_equation, &postfix_eq_position, current_char);
            } else if( current_char == '(') {
                push(stack, current_char);
            } else if (isOperator(current_char)) {
                char right_char = pop(stack);

                while(isOperator(right_char) && getPredecence(right_char) >= getPredecence(current_char)) {
                    updatePostfixEquation(postix_equation, &postfix_eq_position, right_char);
                    right_char = pop(stack);
                }
                push(stack, right_char);
                push(stack, current_char);
                
            } else if (current_char == ')'){
                char right_char = pop(stack);

                while(right_char != '(') {
                    updatePostfixEquation(postix_equation, &postfix_eq_position, right_char);
                    right_char = pop(stack);
                }
            } else {
                printf("caca\n");
            }


            infix_eq_position += 1;
        }

        printPostfixEquation(postix_equation);
        if(!cin.eof()) {printf("\n"); } // Consecutive case

    }



    return 0;
}


void readInput(char * infix_equation){
    string line;
    int char_id = 0;
    for(; char_id < __MAX_LINES__; char_id++){
        getline(cin, line);
        if(line.size() == 0) { break; }
        stringstream input_equation(line);

        char current_char;
        input_equation >> current_char;
        // printf("-- Readed char: %c\n", current_char);
        infix_equation[char_id] = current_char;

        if(cin.eof()) { char_id += 1; break; }
    }
    infix_equation[char_id] = ')';
    infix_equation[char_id + 1] = '\0';
}


void updatePostfixEquation(char*eq, int * pos, char val) {
    eq[*pos] = val;
    ++(*pos);
    eq[*pos] = '\0';
}


// void printPostfixEquation(Stack* stack_postfix) {
//     while(!isEmpty(stack_postfix)) {
//         printf("Res: %c\n", pop(stack_postfix));
//     }
// }

void printPostfixEquation(char* stack_postfix) {
    for(int i = 0; i <= __MAX_LINES__ + 4 && stack_postfix[i] != '\0'; ++i) {
        printf("%c", stack_postfix[i]);
    }

    printf("\n");
}


int getPredecence(char c) {
    if(c == '*' || c == '/') {
        return __PRECEDENCE_HIGH__;
    } else if(c == '+' || c == '-'){
        return __PRECEDENCE_LOW__;
    }

    return __PRECEDENCE_UNKN__;
}


bool isDigit(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

bool isOperator(char c) {
    switch(c){
        case '+':
            return true;
        case '-':
            return true;
        case '*':
            return true;
        case '/':
            return true;
        default:
            return false;
    }
    return false;
}






















/**
 * 
 * 
 * 
 * STACK
 * 
 */

  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* createStack(unsigned capacity) 
{ 
    // printf("[INFO] creating stack size %d\n", capacity);
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack)); 
    stack->capacity = capacity; 
    stack->top = -1; 
    stack->array = (char*)malloc(stack->capacity * sizeof(char)); 
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
void push(struct Stack* stack, char item) 
{ 
    if (isFull(stack)) 
        return; 
    stack->array[++stack->top] = item; 
    // printf("%d pushed to stack\n", item); 
} 
  
// Function to remove an item from stack.  It decreases top by 1 
char pop(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return '\0'; 
    return stack->array[stack->top--]; 
} 
  
// Function to return the top from stack without removing it 
char peek(struct Stack* stack) 
{ 
    if (isEmpty(stack)) 
        return '\0'; 
    return stack->array[stack->top]; 
} 