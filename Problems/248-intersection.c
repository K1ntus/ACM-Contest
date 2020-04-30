#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

typedef struct {
    int x,y;
} point_struct;


// typedef struct {
//     point_struct A,B;
// } line_struct;

// typedef struct {
//     point_struct top_left;
//     point_struct top_right;
//     point_struct bottom_left;
//     point_struct bottom_right;
// } rectangle_struct;

typedef struct {
    //Line
    int xStart, yStart;
    int xEnd,   yEnd;

    //Square
    int xLeft, xRight;
    int yTop, yBottom;
} input_struct;

bool evaluate(input_struct * data);

int main (void){
    int __nb_tests__ = 0;
    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_tests__;


    for(int test_id = 0; test_id < __nb_tests__; test_id++) {
        getline(cin, line);
        stringstream myString(line);

        input_struct * input_data = (input_struct*) malloc(sizeof(input_struct));

        myString >> input_data->xStart 
            >> input_data->yStart 
            >> input_data->xEnd
            >> input_data->yEnd
            >> input_data->xLeft
            >> input_data->yTop
            >> input_data->xRight
            >> input_data->yBottom;

        evaluate(input_data);

    }
    // scanf("%d",&number_of_tests);
    // fprintf(stderr, "There will be %d Tests Case.\n", number_of_tests);

    // input_struct * input_data = (input_struct*) malloc(sizeof(input_struct));

    // scanf("%d %d %d %d %d %d %d %d", 
    //     &input_data->xStart, 
    //     &input_data->yStart,
    //     &input_data->xEnd,
    //     &input_data->yEnd,
    //     &input_data->xLeft,
    //     &input_data->yTop,
    //     &input_data->xRight,
    //     &input_data->yBottom
    // );

    // printf("OK.\n");

    // int res = isInsideRectangle(*input_data) || isIntersectRectangle(*input_data);

    // if (res == 0)
    //     printf("T\n");
    // else
    //     printf("F\n");
    
    // free(input_data);
    return EXIT_SUCCESS;
}

void printData(input_struct data) {
    printf("Data to analyze:\n");
    printf("Segment:\n");
    printf(" * %d %d\n", data.xStart, data.yStart);
    printf(" * %d %d\n", data.xEnd, data.yEnd);
    printf("Square:\n");
    printf("%d %d %d %d\n", data.xLeft, data.yTop, data.xRight, data.yBottom);
}



bool isInsideRectangle(input_struct input);
int isIntersectRectangle(input_struct input);

bool evaluate(input_struct * data) {
    printData(*data);

    bool res = false;

    bool insideRect = isInsideRectangle(*data);
    if(insideRect){
        printf("Segment is Inside rectangle!\n");
    }

    bool intersectRect = isIntersectRectangle(*data);
    if(intersectRect){
        printf("Segment intersect rectangle!\n");
    }

    return res;
}



/**
 * Return 0 if the line segment is inside the rectangle. 
 * Else, it is returning 1
 */
bool isInsideRectangle(input_struct input) {
    if(input.xStart >= input.xLeft && input.xEnd <= input.xRight){
        return true;
    }

    if(input.yStart >= input.yBottom && input.yEnd <= input.yTop){
        return true;
    }

    return false;
}

int isIntersectRectangle(input_struct input) {
    if(input.xStart < input.xLeft && input.xEnd > input.xLeft) {
        return 0;
    }
    // else if (input.xStart > input.xRight && )
    return 1;
}