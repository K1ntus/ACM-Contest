
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

int main (void){
    int number_of_tests = 0;
    scanf("%d",&number_of_tests);
    fprintf(stderr, "There will be %d Tests Case.\n", number_of_tests);

    input_struct * input_data = (input_struct*) malloc(sizeof(input_struct));

    scanf("%d %d %d %d %d %d %d %d", 
        &input_data->xStart, 
        &input_data->yStart,
        &input_data->xEnd,
        &input_data->yEnd,
        &input_data->xLeft,
        &input_data->yTop,
        &input_data->xRight,
        &input_data->yBottom
    );

    printf("OK.\n");

    int res = isInsideRectangle(*input_data) || isIntersectRectangle(*input_data);

    if (res == 0)
        printf("T\n");
    else
        printf("F\n");
    
    free(input_data);
    return res;
}