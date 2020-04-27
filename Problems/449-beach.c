#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;


#define LAND '#'
#define SEA '.'
#define __NB_FRONTIER__ 6
#define __SIZE_ELEMENT_KINGDOM__ 50
#define MAX_WIDTH 50    //[1;50] inclusif
#define MAX_HEIGHT 50   //[1;50] inclusif

// Une position entière dans la grille.
typedef struct {
    int x, y;
} position;

// Une grille.
typedef struct {
    int X, Y;       // dimensions: X et Y
    int **value;    // valuation des cases: value[i][j], 0<=i<X, 0<=j<Y
    int **mark;     // marquage des cases: mark[i][j], 0<=i<X, 0<=j<Y
} grid;

// Valeurs possibles des cases d'une grille pour les champs .value et
// .mark. L'ordre est important: il doit être cohérent avec les
// tableaux color[] (tools.c) et weight[] (a_star.c).
enum {

    // pour .value
    V_LAND,     // empty cell
    V_WATER,    // queen
    V_WALL      // game frontier
};


//
// Alloue une grille aux dimensions x,y ainsi que son image. On force
// x,y>=3 pour avoir au moins un point qui n'est pas sur le bord.
//
static grid* AllocGrid(int width, int height) {
    // int x = 50;
    // int y = 50;
    int x = width + 6;
    int y = height + 6;
    grid *G = (grid *) malloc(sizeof(grid));
    //   if (x < 1)
    //     x = 1;
    //   if (y < 1)
    //     y = 1;

    G->X = x;
    G->Y = y;
    G->value = (int**) malloc(x * sizeof(*(G->value)));
    G->mark  = (int**) malloc(x * sizeof(*(G->mark)));

    for (int i = 0; i < x; i++) {
        G->value[i] = (int*) malloc(y * sizeof(*(G->value[i])));
        G->mark[i] = (int*) malloc(y * sizeof(*(G->mark[i])));

        if(G->mark[i] == 0x0 || G->value[i] == 0x0) {
            fprintf(stderr, "Unable to alloc memory.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < y; j++) {
            G->value[i][j] = V_WALL;
        }
    }

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
        if(y%2 == 0) printf("* ");
        for(int x = 0; x < G.X; x++){
            if(G.value[x][y] == 3) printf("x ");
            else if(G.value[x][y] == V_WALL) printf("* ");
            else if(G.value[x][y] == V_LAND) printf("# ");
            else if(G.value[x][y] == V_WATER) printf("_ ");
            else printf("%d ", G.value[x][y]);
        }
        printf("\n");
    }
    printf("* Width: %d\n* Height: %d\n", G.X, G.Y);
}

grid * InitGrid(int size) {
    grid *G = AllocGrid(size,50);

    for(int y = 1; y < G->Y-1; y++){
        for(int x = 1; x < G->X-1; x++){
            G->value[x][y]= V_WALL;
        }
    }
    return G;
}



void MarkCells(grid * G, int x, int y) {

}

position * getLegalMoves(position current_pos) {
    position * array_to_return = (position *) malloc(sizeof(position) * __NB_FRONTIER__);

    array_to_return[0] = {current_pos.x - 1, current_pos.y};
    array_to_return[1] = {current_pos.x + 1, current_pos.y};

    if(current_pos.y%2 == 1){
        //TOP + TOPDROITE
        array_to_return[2] = {current_pos.x - 1, current_pos.y + 1};
        array_to_return[3] = {current_pos.x - 1, current_pos.y};
        //BOT + BOTDROITE
        array_to_return[4] = {current_pos.x + 1, current_pos.y};
        array_to_return[5] = {current_pos.x + 1, current_pos.y + 1};
    } else {

        // Top + Top-Right
        array_to_return[2] = {current_pos.x, current_pos.y - 1};
        array_to_return[3] = {current_pos.x + 1, current_pos.y - 1};

        // Bottom + Bottom-Left
        array_to_return[4] = {current_pos.x, current_pos.y + 1}; //Left
        array_to_return[5] = {current_pos.x - 1, current_pos.y + 1}; //Right

    }

    return array_to_return;
}

int CountBeaches(grid * G, int x, int y) {
    if(x < 0 ||y < 0 || x > G->X || y > G->Y) {
        return 0;
    }

    if(G->value[x][y] != V_LAND) {
        return 0;
    }


    int res = 0;
    position * legalMoves = getLegalMoves({x,y});
    for(int i = 0; i < __NB_FRONTIER__; i++) {
        int x2 = legalMoves[i].x;
        int y2 = legalMoves[i].y;

        if(x2 < 0 ||y2 < 0 || x2 > G->X || y2 > G->Y) {
            continue;
        }

        if(G->value[x2][y2] == V_WATER) {
            res = res + 1;
        }

    }

    return res;
}


int main (void) {
    string line;
    getline(cin, line);

    grid * G = InitGrid(line.size());
    int __grid_size = line.size();

    for(int y = 1; y < MAX_HEIGHT; ++y) {
        stringstream myString(line);

        if(myString.fail() ||myString.eof()) { return EXIT_SUCCESS; }

        char grid_char ='o';
        myString >> grid_char;

        int x = 1;
        while((grid_char == '.' || grid_char == '#') && x <= __grid_size) {
            switch(grid_char) {
                case '.':
                    G->value[x][y] = V_WATER;
                    break;
                case '#':
                    G->value[x][y] = V_LAND;
                    break;
                default:
                    break;
            }

            // printf("Current value to replace: %d %d\n -> %c\n",x,y,grid_char);
            // G->value[x][y] = grid_char;
            myString >> grid_char;
            x=x+1;
        }

        getline(cin, line);

        if(line.empty()){
            G->Y = y + 2;
            for(int i = 0; i < __grid_size + 1; i++) {
                G->value[i][G->Y - 1] = V_WALL;
            }
            break;
        }
    }

    int sum = 0;
    for(int x = 1; x < __grid_size; x++) {
        for(int y = 1; y < MAX_HEIGHT; y++) {

            if(G->value[x][y] == V_LAND)
                sum = sum + CountBeaches(G, x, y);
        }
    }
    printf("GRID RES: %d\n", sum);
    PrintGrid(*G);


    return EXIT_SUCCESS;
}

/**
 

        // New case or end of analytic
        if(line.empty()){
            case_id = case_id - 1;
            __isEquilibrium = true;
            if(case_id < __nb_cases__) printf("\n");

            continue;
        }
*/