#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __NO_SOLUCE__ -1
#define __SOLUCE_BOARD__ 0
#define __NB_QUEENS_TO_PLACE__ 8



// typedef struct {
//     char ** solution_list;
//     int size_list;
// } result_struct;

// result_struct * InitDictionnary(void) {
//     result_struct * dico = (result_struct *) malloc(sizeof(result_struct));
//     dico->size_list = 0;
//     dico->solution_list = (char **) malloc(sizeof(char *) * 32);

//     return dico;
// }


typedef struct {
    int x, y;
} position;

typedef struct {
    int X, Y;       // dimensions: X et Y
    int **value;    // valuation des cases: value[i][j], 0<=i<X, 0<=j<Y
    // int **mark;     // marquage des cases: mark[i][j], 0<=i<X, 0<=j<Y
} grid;


enum {

    // pour .value
    V_EMPTY,        // empty cell
    V_QUEEN,     // queen
    V_INSIGHT,  // already in sight of a queen
    V_WALL          // game frontier
};


static grid AllocGrid() {
    int x = 10;
    int y = 10;
    grid G;
    //   if (x < 1)
    //     x = 1;
    //   if (y < 1)
    //     y = 1;

    G.X = x;
    G.Y = y;
    G.value = (int**) malloc(x * sizeof(*(G.value)));

    for (int i = 0; i < x; i++) {
        G.value[i] = (int*) malloc(y * sizeof(*(G.value[i])));

        if( G.value[i] == 0x0) {
            fprintf(stderr, "Unable to alloc memory.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < y; j++) {
            G.value[i][j] = V_WALL;
        }
    }

    return G;
}

grid CopyGrid(grid * grid_to_copy) {
    grid res = AllocGrid();
    
    for(int y = 1; y < res.Y-1; y++){
        for(int x = 1; x < res.X-1; x++){
            res.value[x][y]= grid_to_copy->value[x][y];
        }
    }

    return res;
}

void FreeGrid(grid *G) {
    for(int i = 0; i < G->X; i++){
        free(G->value[i]);
    }
    free(G->value);

    free(G);
}

void PrintGrid(grid G) {
    for(int y = 0; y < G.Y; y++) {
        for(int x = 0; x < G.X; x++){
            if(G.value[x][y] == 3) printf("x ");
            else if(G.value[x][y] == 2) printf("* ");
            else if(G.value[x][y] == 1) printf("Q ");
            else if(G.value[x][y] == 0) printf("_ ");
            else printf("%d ", G.value[x][y]);
        }
        printf("\n");
    }
    printf("* Width: %d\n* Height: %d\n", G.X, G.Y);
}


void MarkCellsAfterPlacing(grid * G, int x, int y) {

    //horizontal marks
    for(int x_to_mark = 1; x_to_mark < 9; x_to_mark++){
        if(G->value[x_to_mark][y] == V_EMPTY) {
            G->value[x_to_mark][y] = V_INSIGHT;
        }
    }

    //verticial marks
    for(int y_to_mark = 1; y_to_mark < 9; y_to_mark++){
        if(G->value[x][y_to_mark] == V_EMPTY) {
            G->value[x][y_to_mark] = V_INSIGHT;
        }
    }

    int offset = 1;
    while(x + offset < 9 && y + offset < 9){
        G->value[x + offset][y + offset] = V_INSIGHT;
        offset +=1;
    }
    offset = 1;
    while(x - offset > 0 && y - offset > 0){
        G->value[x - offset][y - offset] = V_INSIGHT;
        offset +=1;
    }
    offset = 1;
    while(x + offset < 9 && y - offset > 0){
        G->value[x + offset][y - offset] = V_INSIGHT;
        offset +=1;
    }
    offset = 1;
    while(x - offset > 0 && y + offset < 9){
        G->value[x - offset][y + offset] = V_INSIGHT;
        offset +=1;
    }

}
void PlaceQueen (grid * G, int x, int y) {
    G->value[x][y] = V_QUEEN;
    MarkCellsAfterPlacing(G, x, y);
}




grid InitGrid(int x_init, int y_init) {
    grid G = AllocGrid();

    for(int y = 1; y < G.Y-1; y++){
        for(int x = 1; x < G.X-1; x++){
            G.value[x][y]= V_EMPTY;
        }
    }


    PlaceQueen(&G, x_init, y_init);

    return G;
}

int NumberAvailableCells(grid * G, int * x_empty, int * y_empty) {
    int res = 0;
    for(int x = 0; x < G->X; x++){
        for(int y = 0; y < G->Y; y++) {
            if(G->value[x][y] == V_EMPTY){
                res += 1;
                *x_empty = x;
                *y_empty = y;
            }
        }
    }
    return res;
}

void RefreshGrid(grid * G) {
    for(int x = 1; x < G->X; x++) {
        for(int y = 1; y < G->Y; y++) {
            if(G->value[x][y] == V_INSIGHT) {
                G->value[x][y] = V_EMPTY;
            }
        }
    }
    for(int x = 1; x < G->X; x++) {
        for(int y = 1; y < G->Y; y++) {
            if(G->value[x][y] == V_QUEEN) {
                PlaceQueen(G, x, y);
            }
        }
    }
}

void RemoveQueenAndRefresh(grid * G, int x, int y) {
    G->value[x][y] = V_EMPTY;
    RefreshGrid(G);
}

int __soln = 0;
void GridToOutputFormat(grid G){
    // char * buffer = (char *) malloc(sizeof(char) * 32);
    int i = 0;
    printf("%2d     ", __soln);
    for(int y = 1; y < G.Y; y++){
        for(int x = 1; x < G.X; x++) {
            if(G.value[x][y] == V_QUEEN)

            printf(" %d", x);
                // buffer[i] = (x);
                // i+=1;
                // buffer[i+1] = ' ';
                // i += 2;
        }
    }
    printf("\n");
    // return buffer;
}

// void AddSolution(grid * G, result_struct * solution_buffer) {
//         char* current_soluce = GridToOutputFormat(*G);
//         for(int i = 0; i < solution_buffer->size_list; i++) {
//         if(current_soluce == solution_buffer->solution_list[i]){
//             free(current_soluce);
//             return;
//         } 
//     }
//     solution_buffer->solution_list[solution_buffer->size_list] = current_soluce;
//     solution_buffer->size_list+=1;
// }
// result_struct * result_buffer;


void PrintSolution(char ** soluces, int nb_cases) {
    // int case = 1;
    // for(; case < nb_cases; case++){
    //     fprintf(stdout, "SOLN\tCOLUMN\n");
    //     fprintf(stdout, " #\t1 2 3 4 5 6 7 8\n");
    //     fprintf(stdout, "\n");
    //     for(int i = 0; i < soluces.size; i++) {
    //         fprintf(stdout, " %d\t%s\n", soluces[i]);
    //     }
    //     fprintf(stdout, "\n");

    // }
}
int SoluceResearch(grid * G, int nb_queens_placed, int x_i, int y_i) {
    int first_x, first_y;
    if(NumberAvailableCells(G, &first_x, &first_y) < __NB_QUEENS_TO_PLACE__ - nb_queens_placed) {
        return __NO_SOLUCE__;
    }

    if(nb_queens_placed >= __NB_QUEENS_TO_PLACE__) {
        // AddSolution(G, result_buffer);
        __soln += 1;
        GridToOutputFormat(*G);
        // PrintGrid(*G);
        return __SOLUCE_BOARD__;
    }
    

    for(int x = 1; x < G->X; x++) {
        for(int y = y_i; y < G->Y; y++) {
            if(G->value[x][y] == V_EMPTY){
                PlaceQueen(G, x, y);
    // PrintGrid(*G);
                SoluceResearch(G, nb_queens_placed + 1, x, y);
                RemoveQueenAndRefresh(G, x, y);
            }
        }
    }

    return __NO_SOLUCE__;
}
int main (void) {

    int __nb_cases__;
    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_cases__;
    getline(cin, line);

    
    for(int case_id = 0; case_id < __nb_cases__; case_id++){
        string line;
        getline(cin, line);
        stringstream myString(line);

        // New case or end of analytic
        if(line.empty()){
            case_id = case_id - 1;
            // printf("\n");
            __soln = 0;
            if(case_id < __nb_cases__) printf("\n");

            continue;
        }


        printf("SOLN       COLUMN\n");
        printf(" #      1 2 3 4 5 6 7 8\n");
        printf("\n");

        int x,y;
        myString >> x >> y;

        grid G = InitGrid(x,y);

        SoluceResearch(&G, 1, 1, 1);
        // FreeGrid(&G);

    }



    return EXIT_SUCCESS;
}