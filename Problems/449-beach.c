#include <stdio.h>
#include <stdlib.h>

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
static grid AllocGrid(int width, int height) {
    int x = 50;
    int y = 50;
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
            G.value[i][j] = V_WALL;
        }
    }

    return G;
}


position* GetAvailableMove(grid * G, int x, int y) {
    position *possible_move = (position *) malloc(sizeof(position) * 8);

    // Case 1
    possible_move[0].x = x+1;
    possible_move[0].y = y+1;

    // Case 1
    possible_move[1].x = x-1;
    possible_move[1].y = y+1;

    // Case 1
    possible_move[2].x = x+1;
    possible_move[2].y = y-1;

    // Case 1
    possible_move[3].x = x+1;
    possible_move[3].y = y-1;


    // Case 1
    possible_move[4].x = x-1;
    possible_move[4].y = y-1;

    // Case 1
    possible_move[5].x = x-1;
    possible_move[5].y = y+1;

    // Case 1
    possible_move[6].x = x-1;
    possible_move[6].y = y;

    // Case 1
    possible_move[7].x = x+1;
    possible_move[7].y = y;


    return possible_move;
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

grid InitGrid() {
    grid G = AllocGrid(50,50);

    for(int y = 1; y < G.Y-1; y++){
        for(int x = 1; x < G.X-1; x++){
            G.value[x][y]= V_WATER;
        }
    }

    return G;
}

void MarkCells(grid * G, int x, int y) {

}



int main (void) {
    grid G = InitGrid();
    // printf("\n\n\n");
    // int ** soluce_array = (int **) malloc(sizeof())

    PrintGrid(G);
    // printf("%d\n", res);

    // FreeGrid(&G);


    return EXIT_SUCCESS;
}