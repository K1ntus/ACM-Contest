#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __MAX_NB_MOVES__ 4 //Max nb of moves per turn (top, bot, left, right)
#define __MAXIMUM_COST__ 125
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
    V_EMPTY,        // empty cell
    V_MARKED,     // queen
    V_WALL          // game frontier
};




struct Stack * getLegalMoves(grid G, position p);


grid InitGrid(int size);
void PrintGrid(grid G);

int MoveRover(grid * G, position current_position, position destination_position, int flow, int bestFlow);


int main (void) {

    string line;
    int __grid_size__;
    getline(cin, line);
    stringstream myString(line);
    myString >> __grid_size__;

    int __problem_number = 1;

    while(__grid_size__ > 0) {

        grid G = InitGrid(__grid_size__);
        // PrintGrid(G);

        int res = MoveRover(&G, {1,1}, {__grid_size__,__grid_size__}, 0, __MAXIMUM_COST__ * __MAXIMUM_COST__);

        printf("Problem %d: %d\n", __problem_number, res);


        getline(cin, line);
        stringstream myString(line);
        myString >> __grid_size__;
        __problem_number += 1;
    }

    return EXIT_SUCCESS;
}






position * getLegalMoves(grid * G, position p) {
    position * res = (position *) malloc(sizeof(position) * __MAX_NB_MOVES__);

    res[0]={p.x - 1, p.y};
    res[1]={p.x + 1, p.y};
    res[2]={p.x, p.y - 1};
    res[3]={p.x, p.y + 1};

    return res;
}


int MoveRover(grid * G, position current_position, position destination_position, int flow, int bestFlow) {
    if(current_position.x == destination_position.x && current_position.y == destination_position.y) {
        return flow + G->value[destination_position.x][destination_position.y];
    }

    if(flow >= bestFlow) {
        return flow * 10;
    }

    position * legalMoves = getLegalMoves(G, current_position);

    G->mark[current_position.x][current_position.y] = V_MARKED;
    for(int move = 0; move < __MAX_NB_MOVES__; ++move) {
        position nextMove = legalMoves[move];
        if(G->mark[nextMove.x][nextMove.y] != V_EMPTY) { continue; }

        int val = MoveRover(G, nextMove, destination_position, flow + G->value[current_position.x][current_position.y], bestFlow);

        if(val < bestFlow) {
            bestFlow = val;
        }

    }

    G->mark[current_position.x][current_position.y] = V_EMPTY;
    free(legalMoves);

    return bestFlow;
}






//
// Alloue une grille aux dimensions x,y ainsi que son image. On force
// x,y>=3 pour avoir au moins un point qui n'est pas sur le bord.
//
static grid AllocGrid(int size) {
    int x = size + 2;
    int y = size + 2;
    grid G;

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
            G.value[i][j] = 126;
            G.mark[i][j] = V_WALL;
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
        for(int x = 0; x < G.X; x++){
            if(G.mark[x][y] == V_WALL) printf("# ");
            else if(G.mark[x][y] == V_EMPTY) printf("%d ", G.value[x][y]);
            else printf("%d ", G.value[x][y]);
        }
        printf("\n");
    }
    printf("* Width: %d\n* Height: %d\n", G.X, G.Y);
}

grid InitGrid(int size) {
    grid G = AllocGrid(size);
    string line;

    for(int y = 1; y < G.Y-1; y++){
        getline(cin, line);
        stringstream myString(line);

        for(int x = 1; x < G.X-1; x++){
            int val;
            myString >> val;
            G.value[x][y]= val;
            G.mark[x][y] = V_EMPTY;
        }
    }

    return G;
}

