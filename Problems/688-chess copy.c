#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __NO_SOL_FOUND__ 4096
// Une position entière dans la grille.
typedef struct {
    int x, y;
} position;

// Une grille.
typedef struct {
    int X, Y;       // dimensions: X et Y
    int **value;    // valuation des cases: value[i][j], 0<=i<X, 0<=j<Y
} grid;

// Valeurs possibles des cases d'une grille pour les champs .value et
// .mark. L'ordre est important: il doit être cohérent avec les
// tableaux color[] (tools.c) et weight[] (a_star.c).
enum {

    // pour .value
    V_EMPTY,        // empty cell
    V_OCCUPIED,     // queen
    V_WHITE_KNIGHT,  
    V_BLACK_KNIGHT,  
    V_WALL,         // game frontier
    V_TESTED
};

void AddCell(grid * G, int x, int y, char type);
int white_x = 0;
int white_y = 0;
int black_x = 0;
int black_y = 0;
int __nb_case__ = -1;
//
// Alloue une grille aux dimensions x,y ainsi que son image. On force
// x,y>=3 pour avoir au moins un point qui n'est pas sur le bord.
//
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

        if(G.value[i] == 0x0) {
            fprintf(stderr, "Unable to alloc memory.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < y; j++) {
            G.value[i][j] = V_WALL;
        }
    }

    return G;
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
            if(G.value[x][y] == 4) printf("x ");
            else if(G.value[x][y] == 3) printf("# ");
            else if(G.value[x][y] == 2) printf("@ ");
            else if(G.value[x][y] == 1) printf("* ");
            else if(G.value[x][y] == 0) printf("- ");
            else printf("%d ", G.value[x][y]);
        }
        printf("\n");
    }
    printf("* Width: %d\n* Height: %d\n", G.X, G.Y);
}

void AddCell(grid * G, int x, int y, char type) {
    switch (type) {
        case '#':
            G->value[x][y] = V_BLACK_KNIGHT;
            black_x = x;
            black_y = y;
        break;
        case '@':
            G->value[x][y] = V_WHITE_KNIGHT;
            white_x = x;
            white_y = y;
        break;
        case '*':
            G->value[x][y] = V_OCCUPIED;
        break;
        default: 
            G->value[x][y] = V_EMPTY;
        break;
    }
}

grid InitGrid() {
    grid G = AllocGrid();

    for(int y = 1; y < G.Y-1; y++){
        for(int x = 1; x < G.X-1; x++){
            G.value[x][y]= V_EMPTY;
        }
    }


    for(int y = 1; y < G.Y-1; y++){
        string line;
        getline(cin, line);
        stringstream myString(line);
        // for(int y = 1; y < G.Y-1; y++){
        char x1, x2, x3, x4, x5, x6, x7, x8;

        for(int x = 1; x < G.X-1; x++){
            char type = '?';
            myString >> type;
            AddCell(&G, x, y, type);
        }
    }
    return G;
}

position* GetAvailableMove(grid * G, int x, int y) {
    position *possible_move = (position *) malloc(sizeof(position) * 8);

    // Case 1
    possible_move[0].x = x+1;
    possible_move[0].y = y+2;

    // Case 1
    possible_move[1].x = x+1;
    possible_move[1].y = y-2;

    // Case 1
    possible_move[2].x = x+2;
    possible_move[2].y = y+1;

    // Case 1
    possible_move[3].x = x+2;
    possible_move[3].y = y-1;


    // Case 1
    possible_move[4].x = x-1;
    possible_move[4].y = y-2;

    // Case 1
    possible_move[5].x = x-1;
    possible_move[5].y = y+2;

    // Case 1
    possible_move[6].x = x-2;
    possible_move[6].y = y-1;

    // Case 1
    possible_move[7].x = x-2;
    possible_move[7].y = y+1;


    return possible_move;
}

bool IsValidPosition(grid * G, position p) {
    int x = p.x;
    int y = p.y;

    if(p.x < 1 || p.x > 8) return false;
    if(p.y < 1 || p.x > 8) return false;

    if(G->value[x][y] != V_EMPTY && G->value[x][y] != V_WHITE_KNIGHT) return false;

    return true;
}


grid CreateAndCopyGrid(grid * G){
    grid res = AllocGrid();

    for(int x = 0; x < G->X; x++){
        for(int y = 0; y < G->Y; y++) {
            res.value[x][y] = G->value[x][y];
        }
    }

    return res;
}

int MoveKnight(grid * G, int x, int y, int count, bool workOverGridCopy) {
    position * available_move = GetAvailableMove(G, x, y);
    if(G->value[x][y] == V_WHITE_KNIGHT) {
        return count;
    } else if(G->value[x][y] == V_TESTED) {
        return __NO_SOL_FOUND__;
    } else {
        G->value[x][y] = V_TESTED;
    }

    int res = __NO_SOL_FOUND__;
    for(int i = 0; i < 8; i++) {
        position current_move = available_move[i];
        if(IsValidPosition(G, current_move)) {
            int tmp_value = res;
            if(workOverGridCopy){
                grid G_copy = CreateAndCopyGrid(G);
                tmp_value = MoveKnight(&G_copy, current_move.x, current_move.y, count + 1, false);
            } else tmp_value = MoveKnight(G, current_move.x, current_move.y, count + 1, false);
            if(tmp_value >= __NO_SOL_FOUND__) continue;
            if(tmp_value < res) res = tmp_value;
        }
    }
    if(res == __NO_SOL_FOUND__)
        return __NO_SOL_FOUND__;
    return res;
}


int main (void) {
    grid G;
    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_case__;
    for(int case_number = 0; case_number < __nb_case__; case_number++){
        G = InitGrid();
        // printf("\n\n\n");

        // PrintGrid(G);
        int res = MoveKnight (&G, black_x, black_y, 0, true);
        if(res >= __NO_SOL_FOUND__) printf("Case %d: IMPOSSIBLE\n", case_number+1);
        else printf("Case %d: %d\n", case_number+1, res);
        // if(case_number < __nb_case__) printf("\n");
        // FreeGrid(&G);
        if(case_number < __nb_case__-1 && __nb_case__ > 1) {
            char bullshit_buffer[8];
            fgets(bullshit_buffer, 8, stdin); //emptyline cleaning
        }  
    }

    return EXIT_SUCCESS;
}