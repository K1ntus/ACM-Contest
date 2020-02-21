#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __NO_SOL_FOUND__ 4096

#define __TOP_BORDER_ID__ 0
#define __BOTTOM_BORDER_ID__ 9
#define __LEFT_BORDER_ID__ 0
#define __RIGHT_BORDER_ID__ 9
#define __MAX_NB_MOVE__ 8

// Une position entière dans la grille.
typedef struct {
    int x, y;
} position;

// Une grille.
typedef struct {
    int X, Y;       // dimensions: X et Y
    int **value;    // valuation des cases: value[i][j], 0<=i<X, 0<=j<Y
    //Save position black and white knight here
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

#define __CHAR_WHITE_KNIGHT__ '@'
#define __CHAR_BLACK_KNIGHT__ '#'
#define __CHAR_WALL__ 'x'
#define __CHAR_EMPTY__ '-'
#define __CHAR_OCCUPIED__ '*'

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

    G.X = x;
    G.Y = y;
    G.value = (int**) malloc(x * sizeof(*(G.value)));

    for (int i = 0; i < x; i++) {
        G.value[i] = (int*) malloc(y * sizeof(*(G.value[i])));

        if(G.value[i] == 0x0) {
            fprintf(stdout, "Unable to alloc memory.\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < y; j++) {
            G.value[i][j] = V_WALL;
        }
    }

    return G;
}

void FreeGrid(grid *G) {
    for(int i = 0; i <= __RIGHT_BORDER_ID__; i++){
        // free(G->value[i]);
    }
    free(G->value);

    // free(G);
}

void PrintGrid(grid G) {
    //Dup2 for stdout <- stdout
    for(int y = 0; y <= __BOTTOM_BORDER_ID__; y++) {
        for(int x = 0; x <= __RIGHT_BORDER_ID__; x++){
            if(G.value[x][y] == V_WALL) fprintf(stdout, "x ");
            else if(G.value[x][y] == V_BLACK_KNIGHT) fprintf(stdout, "# ");
            else if(G.value[x][y] == V_WHITE_KNIGHT) fprintf(stdout, "@ ");
            else if(G.value[x][y] == V_OCCUPIED) fprintf(stdout, "* ");
            else if(G.value[x][y] == V_EMPTY) fprintf(stdout, "- ");
            else fprintf(stdout, "%d ", G.value[x][y]);
        }
        fprintf(stdout, "\n");
    }
    // fprintf(stdout, "* Width: %d\n* Height: %d\n", G.X, G.Y);
    //dup restore stdout
}

char IntegerToChar(int type) {
    switch(type){
        case V_BLACK_KNIGHT:
            return __CHAR_BLACK_KNIGHT__;
        case V_WHITE_KNIGHT:
            return __CHAR_WHITE_KNIGHT__;
        case V_OCCUPIED:
            return __CHAR_OCCUPIED__;
        default:
            return __CHAR_EMPTY__;
    }
}

void AddCell(grid * G, int x, int y, char type) {
    switch (type) {
        case __CHAR_BLACK_KNIGHT__:
            G->value[x][y] = V_BLACK_KNIGHT;
            black_x = x;
            black_y = y;
        break;
        case __CHAR_WHITE_KNIGHT__:
            G->value[x][y] = V_WHITE_KNIGHT;
            white_x = x;
            white_y = y;
        break;
        case __CHAR_OCCUPIED__:
            G->value[x][y] = V_OCCUPIED;
        break;
        default: 
            G->value[x][y] = V_EMPTY;
        break;
    }
}

grid InitGrid() {
    grid G = AllocGrid();

    for(int y = 1; y < __BOTTOM_BORDER_ID__; y++){
        for(int x = 1; x < __RIGHT_BORDER_ID__; x++){
            G.value[x][y]= V_EMPTY;
        }
    }


    for(int y = 1; y < __BOTTOM_BORDER_ID__; y++){
        string line;
        getline(cin, line);
        stringstream myString(line);
        // for(int y = 1; y < G.Y-1; y++){
        char x1, x2, x3, x4, x5, x6, x7, x8;

        for(int x = 1; x < __RIGHT_BORDER_ID__; x++){
            char type = '?';
            myString >> type;
            AddCell(&G, x, y, type);
        }
    }
    return G;
}


//Use a stack implementation
position* GetAvailableMove(grid * G, int x, int y) {
    position *possible_move = (position *) malloc(sizeof(position) * __MAX_NB_MOVE__);

    // Case 1
    possible_move[5].x = x+1;
    possible_move[5].y = y+2;

    // Case 1
    possible_move[6].x = x+1;
    possible_move[6].y = y-2;

    // Case 1
    possible_move[7].x = x+2;
    possible_move[7].y = y+1;

    // Case 1
    possible_move[3].x = x+2;
    possible_move[3].y = y-1;


    // Case 1
    possible_move[4].x = x-1;
    possible_move[4].y = y-2;

    // Case 1
    possible_move[0].x = x-1;
    possible_move[0].y = y+2;

    // Case 1
    possible_move[1].x = x-2;
    possible_move[1].y = y-1;

    // Case 1
    possible_move[2].x = x-2;
    possible_move[2].y = y+1;


    return possible_move;
}

bool IsValidPosition(grid * G, position p) {
    int x = p.x;
    int y = p.y;

    if(x < __LEFT_BORDER_ID__ || x > __RIGHT_BORDER_ID__ ) return false;
    if(y < __TOP_BORDER_ID__  || y > __BOTTOM_BORDER_ID__) return false;

    if( G->value[x][y] == V_WALL 
        || G->value[x][y] == V_OCCUPIED 
        || G->value[x][y] == V_TESTED) 
            return false;

    return true;
}


grid CreateAndCopyGrid(grid G){
    grid res = AllocGrid();

    for(int x = 1; x < __RIGHT_BORDER_ID__; x++){
        for(int y = 1; y < __BOTTOM_BORDER_ID__; y++) {
            AddCell(&res, x, y, IntegerToChar(G.value[x][y]));
        }
    }

    return res;
}

grid ClearTestedGrid(grid * G){
    grid res = AllocGrid();

    for(int x = 1; x < __RIGHT_BORDER_ID__; x++){
        for(int y = 1; y < __BOTTOM_BORDER_ID__; y++) {
            if(G->value[x][y] == V_TESTED) G->value[x][y] == V_EMPTY;
            // AddCell(&res, x, y, IntegerToChar(G.value[x][y]));
        }
    }

    return res;
}

int MoveKnight(grid * G, position current_pos, int count) {
    if(! IsValidPosition(G, current_pos)){
        return __NO_SOL_FOUND__;
    } else if(G->value[current_pos.x][current_pos.y] == V_WHITE_KNIGHT) {
    // fprintf(stdout, "Find following board. Size = %d\n", count);
    // PrintGrid(*G);
        ClearTestedGrid(G);
        return count;
    }

    position * available_move = GetAvailableMove(G, current_pos.x, current_pos.y);
    G->value[current_pos.x][current_pos.y] = V_TESTED;

    int res = __NO_SOL_FOUND__;
    for(int i = 0; i < __MAX_NB_MOVE__; i++) {
        position current_move = available_move[i];

        int tmp_value = MoveKnight(G, current_move, count + 1);
        
        if(tmp_value >= __NO_SOL_FOUND__) {
            continue;
        } else if(tmp_value < res){
            // G->value[current_pos.x][current_pos.y] = V_EMPTY;
            res = tmp_value; 
        } 
    }

    if(res != __NO_SOL_FOUND__) {    //If path leads to at least one solution we clear the path for later
        G->value[current_pos.x][current_pos.y] = V_EMPTY;
    } else {
        ClearTestedGrid(G);
    }

    return res;
}


void ChessBoardAnalyze_wrapper(grid G, int case_number) {
    int res = __NO_SOL_FOUND__;
    position * available_move = GetAvailableMove(&G, black_x, black_y);

    for(int i = 0; i < __MAX_NB_MOVE__; i++) {

        position current_move = available_move[i];
        if(IsValidPosition(&G, current_move)) {
            int tmp_value = res;

            grid G_copy = CreateAndCopyGrid(G);
            G.value[current_move.x][current_move.y] = V_TESTED;
            tmp_value = MoveKnight(&G_copy, current_move, 1);

            if(tmp_value < res) res = tmp_value;
            FreeGrid(&G_copy);
        }

    }

    if(res >= __NO_SOL_FOUND__) fprintf(stdout, "Case %d: IMPOSSIBLE", case_number + 1);
    else fprintf(stdout, "Case %d: %d", case_number + 1, res);    
}

int main (void) {
    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> __nb_case__;

    for(int case_number = 0; case_number < __nb_case__; case_number++){
        grid G = InitGrid();

        ChessBoardAnalyze_wrapper(G, case_number);

        if(case_number < __nb_case__ - 1 && __nb_case__ > 1) {    //More than 1 case and not the last case
            char bullshit_buffer[8];
            fgets(bullshit_buffer, 8, stdin); //emptyline cleaning
            fprintf(stdout, bullshit_buffer);
        } 

        FreeGrid(&G);
    }
    fprintf(stdout, "\n");

    return EXIT_SUCCESS;
}