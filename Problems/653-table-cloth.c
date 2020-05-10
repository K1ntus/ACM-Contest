#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


typedef struct {
    int x, y;
} position;

// Une grille.
typedef struct {
    int X, Y;       // dimensions: X et Y
    int **value;    // valuation des cases: value[i][j], 0<=i<X, 0<=j<Y
    int **mark;     // marquage des cases: mark[i][j], 0<=i<X, 0<=j<Y

    position* stick_position;
    int __nb_sticks;
} grid;

grid InitGrid(int w, int h);

void PrintGrid(grid G);
// Valeurs possibles des cases d'une grille pour les champs .value et
// .mark. L'ordre est important: il doit être cohérent avec les
// tableaux color[] (tools.c) et weight[] (a_star.c).
enum {

    // pour .value
    V_EMPTY,        // empty cell
    V_OCCUPIED,     // queen
    // V_UNAVAILABLE,  // already in sight of a queen
    V_STICK,
    V_WALL          // game frontier
};


enum {
    C_TOPLEFT,
    C_TOPRIGHT,
    C_BOTTOMLEFT,
    C_BOTTOMRIGHT
};





void BubbleSort(int *arr, int n); 
void swap(int *xp, int *yp);
void printArray(int *arr, int size);
int getNbEmptyCells(grid G);
int applyTableCloth(grid * G, int __corner, position * flipped_position, position stick_position);
void solveTable(grid * G);

int main (void) {
    int __width, __height; 

    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __height >> __width;


    while(__height != 0 && __width != 0) {

        grid G = InitGrid(__width, __height);
        for(int y = 1; y < __height + 1; y++) {
            getline(cin, line);
            stringstream myString(line);

            for(int x = 1; x < __width + 1; x++) {
                int val;
                myString >> val;

                if(val == 0) {
                    G.mark[x][y] = V_EMPTY;
                } else {
                    G.mark[x][y] = V_STICK;
                    G.stick_position[G.__nb_sticks] = {x,y};
                    G.__nb_sticks+=1;
                }
            }
        }


        /** 
         * DEBUG
        **/
        // PrintGrid(G);
        // printf("* %d Sticks available:\n", G.__nb_sticks);
        // for(int i = 0; i < G.__nb_sticks; ++i) {
        //     printf("* (%d,%d)\n", G.stick_position[i]);
        // }

        int __nb_moves = 0;
        while(getNbEmptyCells(G) > 0) {
            solveTable(&G);
            __nb_moves += 1;
        printf("RES: %d\n", __nb_moves);
        }

        printf("FINL RES: %d\n", __nb_moves);
        getline(cin, line);
        stringstream myString(line);
        myString >> __height >> __width;
    }

    // BubbleSort(person_array, __nb_people__);
    // //printArray(person_array, __nb_people__);
    // fprintf(stdout, "%s\n", person_array[__nb_people__-1]);
    // fprintf(stdout, "%s\n", person_array[0]);

    return EXIT_SUCCESS;
}



void solveTable(grid * G) {
    position * list_best_move;
    int best_value = -1;
    for(int __direction = 0; __direction < 4; __direction++) {
        position * flipped_position = (position *) malloc(sizeof(position) * G->Y * G->X);
        for(int i = 0; i < G->Y*G->X; ++i) {
            flipped_position[i] = {0,0};
        }
        
        
        for(int stick_id = 0; stick_id < G->__nb_sticks; ++stick_id) {
            int value = applyTableCloth(G, __direction, flipped_position, G->stick_position[stick_id]);

            if(value > best_value) {
                best_value = value;
                list_best_move = flipped_position;
            }
        }
    }

    printf("Best_move value is: %d\n", best_value);

    for(int i = 0; i < G->X * G->Y; ++i) {
        if(list_best_move[i].x == 0 && list_best_move[i].y == 0) { break; }
        G->mark[list_best_move[i].x][list_best_move[i].y] = V_OCCUPIED;
    }
}

int applyTableCloth(grid * G, int __corner, position * flipped_position, position stick_position) {
    int nb_cells_newly_occupied = 0;


    int dest_x = stick_position.x;
    int dest_y = stick_position.y;
    int offset_x, offset_y;
    switch (__corner) {
    case C_BOTTOMLEFT:
        offset_x = 0;
        offset_y = dest_y;
        break;
    case C_BOTTOMRIGHT:
        offset_x = dest_x;
        offset_y = dest_y;
        break;
    case C_TOPLEFT:
        offset_x = 0;
        offset_y = 0;
        break;
    case C_TOPRIGHT:
        offset_x = dest_x;
        offset_y = 0;
        break;
    default:
        offset_x = 0;
        offset_y = 0;
        break;
    }


    int i = 0;
    for(int y = offset_y; y < G->Y; ++y) {
        for(int x = offset_x; x < G->X; ++x) {
            if(G->mark[x][y] == V_WALL) { continue; }

            if(G->mark[x][y] == V_EMPTY) { 
                ++nb_cells_newly_occupied; 
                flipped_position[i] = {x,y};
                ++i;
                // G->mark[x][y] == V_OCCUPIED;
            }

        }
    }

    return nb_cells_newly_occupied;
}




int getNbEmptyCells(grid G) {
    int res = 0;
    for(int x = 1; x < G.X; ++x) {
        for(int y = 1; y < G.Y; ++y) {
            if(G.mark[x][y] == V_EMPTY) {
                ++res;
            }
        }
    }
    return res;
}













/* Function to print an array */
void printArray(int *arr, int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("(%s,%d) ", arr[i], arr[i]); 
    printf("\n"); 
} 
void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void BubbleSort(int *arr, int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 
















/**
 * 
 * GRID
 * 
 */


//
// Alloue une grille aux dimensions x,y ainsi que son image. On force
// x,y>=3 pour avoir au moins un point qui n'est pas sur le bord.
//
static grid AllocGrid(int x, int y) {
    grid G;
    //   if (x < 1)
    //     x = 1;
    //   if (y < 1)
    //     y = 1;

    G.X = x;
    G.Y = y;
    G.value = (int**) malloc(x * sizeof(*(G.value)));
    G.mark  = (int**) malloc(x * sizeof(*(G.mark)));

    for (int i = 0; i < x; i++) {
        G.value[i] = (int*) malloc(y * sizeof(*(G.value[i])));
        G.mark[i] = (int*) malloc(y * sizeof(*(G.mark[i])));

        if(G.mark[i] == 0x0 || G.value[i] == 0x0) {
            fprintf(stderr, "Unable to alloc memory.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < y; j++) {
            G.mark[i][j] = V_WALL;
        }
    }

    G.stick_position = (position *) malloc(sizeof(position) * x * y);
    G.__nb_sticks = 0;

    return G;
}

void FreeGrid(grid *G) {
    for(int i = 0; i < G->X; i++){
        free(G->mark[i]);
        free(G->value[i]);
    }
    free(G->mark);
    free(G->value);

    free(G);
}

void PrintGrid(grid G) {
    for(int y = 0; y < G.Y; y++) {
        for(int x = 0; x < G.X; x++){
            if(G.mark[x][y] == V_STICK) printf("X ");
            else if(G.mark[x][y] == V_WALL) printf("# ");
            else if(G.mark[x][y] == V_EMPTY) printf("_ ");
            else printf("%d ", G.mark[x][y]);
        }
        printf("\n");
    }
    printf("* Width: %d\n* Height: %d\n", G.X, G.Y);
}

grid InitGrid(int w, int h) {
    grid G = AllocGrid(w+2, h+2);

    for(int y = 1; y < G.Y-1; y++){
        for(int x = 1; x < G.X-1; x++){
            G.mark[x][y]= V_WALL;
        }
    }

    return G;
}

void MarkCells(grid * G, int x, int y) {

}
