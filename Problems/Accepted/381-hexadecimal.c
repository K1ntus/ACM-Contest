#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __EQ_SIZE__ 100

char * expressionToParse;

char peek()
{
    return *expressionToParse;
}

char get()
{
    return *expressionToParse++;
}

int val_converter(char c){
        switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
            return -1;
    }
}
int expression();

int number()
{
    int result = val_converter(get());
    while (peek() >= '0' && peek() <= 'F')
    {
        result = 10*result + val_converter(get());
    }
    return result;
}

int factor()
{
    if (peek() >= '0' && peek() <= 'F')
        return number();
    else if (peek() == '(')
    {
        get(); // '('
        int result = expression();
        get(); // ')'
        return result;
    }
    else if (peek() == '-')
    {
        get();
        return -factor();
    }
    return 0; // error
}

int term()
{
    int result = factor();
    while (peek() == '*' || peek() == '/')
        if (get() == '*')
            result *= factor();
        else
            result /= factor();
    return result;
}

int expression()
{
    int result = term();
    while (peek() == '+' || peek() == '-')
        if (get() == '+')
            result += term();
        else
            result -= term();
    return result;
}


// https://stackoverflow.com/questions/9329406/evaluating-arithmetic-expressions-from-string-in-c

int main (void) {
    expressionToParse = (char *) malloc(sizeof(char)  * 10000);
    string line;

    while(getline(cin, line)) {
        stringstream myString(line);
        myString >> expressionToParse;

        // printf("EXPRESSION: %s\n", expressionToParse);
        int result = expression();

        printf("%X\n", result);
    }
}