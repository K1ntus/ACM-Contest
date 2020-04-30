#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __EQ_SIZE__ 100
#define __CHAR_MIN_DIGIT__ '0'
#define __CHAR_MAX_DIGIT__ 'F'

char * expressionToParse;
int expression();

char peek() {
    return *expressionToParse;
}

char get() {
    return *expressionToParse++;
}

int charToInt(char c) {
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

int number() {
    int result = charToInt(get());
    while (peek() >= __CHAR_MIN_DIGIT__ && peek() <= __CHAR_MAX_DIGIT__) {
        result = 10*result + charToInt(get());
    }
    return result;
}

int factor() {
    if (peek() >= __CHAR_MIN_DIGIT__ && peek() <= __CHAR_MAX_DIGIT__)
        return number();
    else if (peek() == '(') {
        get(); // '('
        int result = expression();
        get(); // ')'
        return result;
    }
    return 0; // error
}

int term() {
    int result = factor();
    while (peek() == '*')
        if (get() == '*')
            result *= factor();
    return result;
}

int expression() {
    int result = term();
    while (peek() == '+')
        if (get() == '+')
            result += term();
    return result;
}


// https://stackoverflow.com/questions/9329406/evaluating-arithmetic-expressions-from-string-in-c mostly inspired of
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