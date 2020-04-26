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

int MoveRover(grid * G, position current_position, int flow, int bestFlow);


int dest_pos;
int offset;
int main (void) {

    string line;
    int __grid_size__;
    getline(cin, line);
    stringstream myString(line);
    myString >> __grid_size__;

    int __problem_number = 1;

    while(__grid_size__ > 0) {

        grid G = InitGrid(__grid_size__);
        dest_pos = __grid_size__;
        offset = G.value[dest_pos][dest_pos];
        // PrintGrid(G);

        int res = MoveRover(&G, {1,1}, 0, __MAXIMUM_COST__ * __MAXIMUM_COST__);
        // int res = MoveRover(&G, {1,2}, G.value[1][1], __MAXIMUM_COST__ * __MAXIMUM_COST__);
        // res = MoveRover(&G, {2,1}, G.value[1][1], res);

        printf("Problem %d: %d\n", __problem_number, res);

        getline(cin, line);
        stringstream myString(line);
        myString >> __grid_size__;
        __problem_number += 1;
    }

    return EXIT_SUCCESS;
}






// position * getLegalMoves(grid * G, position p) {
//     position * res = (position *) malloc(sizeof(position) * __MAX_NB_MOVES__);

//     res[0]={p.x - 1, p.y};
//     res[1]={p.x + 1, p.y};
//     res[2]={p.x, p.y - 1};
//     res[3]={p.x, p.y + 1};

//     return res;
// }

int MoveRover(grid * G, position current_position, int flow, int bestFlow) {
    int curr_x = current_position.x;
    int curr_y = current_position.y;

    // Update the current flow value
    flow = flow + G->value[curr_x][curr_y];     


    // If current pos is destination pos, return updated flow
    if(curr_x == dest_pos && curr_y == dest_pos) {
        return flow;
    }

    //If the flow is already greater than the bestFlow, return
    if(flow >= bestFlow - offset) {
        return __MAXIMUM_COST__ * __MAXIMUM_COST__;
    }
    // get the four possibles legalMoves
    position legalMoves[__MAX_NB_MOVES__] = {
        {curr_x - 1, curr_y},
        {curr_x + 1, curr_y},
        {curr_x, curr_y - 1},
        {curr_x, curr_y + 1}
    };

    // Mark the current cell as visited
    G->mark[curr_x][curr_y] = V_MARKED;


    for(int move = 0; move < __MAX_NB_MOVES__; ++move) {
        position nextMove = legalMoves[move];

        // If the cell is a wall, or already been marked, continue
        if(G->mark[nextMove.x][nextMove.y] != V_EMPTY) { continue; }

        // If nextMove+flow will be greater than the bestFlow, continue
        if(flow + G->value[nextMove.x][nextMove.y] > bestFlow) { continue; }

        // Do the recursion
        int val = MoveRover(G, nextMove, flow, bestFlow);

        // Update the bestflow
        if(val < bestFlow) {
            bestFlow = val;
        }

    }

    // Unmark this cells for next recursions
    G->mark[curr_x][curr_y] = V_EMPTY;

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

    for (int i = 0; i < x; ++i) {
        G.value[i] = (int*) malloc(y * sizeof(*(G.value[i])));
        G.mark[i]  = (int*) malloc(y * sizeof(*(G.mark[i])));

        if(G.mark[i] == 0x0 || G.value[i] == 0x0) {
            fprintf(stderr, "Unable to alloc memory.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < y; ++j) {
            G.value[i][j] = 126;
            G.mark[i][j] = V_WALL;
        }
    }

    return G;
}


void FreeGrid(grid *G) {
    for(int i = 0; i < G->X; ++i){
        free(G->mark[i]);
        free(G->value[i]);
    }
    free(G->mark);
    free(G->value);

    free(G);
}

void PrintGrid(grid G) {
    for(int y = 0; y < G.Y; ++y) {
        for(int x = 0; x < G.X; ++x){
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

    for(int y = 1; y < G.Y-1; ++y){
        getline(cin, line);
        stringstream myString(line);

        for(int x = 1; x < G.X-1; ++x){
            myString >> G.value[x][y];
            G.mark[x][y] = V_EMPTY;
        }
    }

    return G;
}

