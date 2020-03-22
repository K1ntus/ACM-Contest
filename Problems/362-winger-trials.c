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
} grid;

// Valeurs possibles des cases d'une grille pour les champs .value et
// .mark. L'ordre est important: il doit être cohérent avec les
// tableaux color[] (tools.c) et weight[] (a_star.c).
enum {

    // pour .value
    V_EMPTY,        // empty cell
    V_ENEMY,     // queen
    V_WINGER,  // already in sight of a queen
    V_TACKLED,
    V_TESTED,
    V_REACHABLE,
    V_WALL          // game frontier
};


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
            if(G.value[x][y] == V_WALL) printf("x ");
            else if(G.value[x][y] == V_WINGER) printf("P ");
            else if(G.value[x][y] == V_TACKLED) printf("* ");
            else if(G.value[x][y] == V_REACHABLE) printf("O ");
            else if(G.value[x][y] == V_ENEMY) printf("# ");
            else if(G.value[x][y] == V_EMPTY) printf("_ ");
            else printf("%d ", G.value[x][y]);
        }
        printf("\n");
    }
    printf("* Width: %d\n* Height: %d\n", G.X, G.Y);
}

grid InitGrid(int x, int y) {
    grid G = AllocGrid(x, y);

    for(int y = 1; y < G.Y-1; y++){
        for(int x = 1; x < G.X-1; x++){
            G.value[x][y]= V_EMPTY;
        }
    }

    return G;
}

void MarkCells(grid * G, int x, int y) {

}

void AddEnemy(grid * G, int x, int y, int tackle_range) {
    for(int xi = x - tackle_range; xi < x + tackle_range; xi++) {
        if(xi > 0 && xi < G->X) {
            for(int yi = y - tackle_range; yi < y + tackle_range; yi++) {
                if(yi > 0 && yi < G->Y) {
                    if(G->value[xi][yi] == V_EMPTY) G->value[xi][yi] = V_TACKLED;
                }
            }
        }
    }

    G->value[x][y] = V_ENEMY;
}

void MarkReachableAreas(grid * G, int x, int y){
    if(G->value[x][y] == V_TACKLED || G->value[x][y] == V_WALL || G->value[x][y] == V_REACHABLE){
        return;
    }

    if(G->value[x][y] == V_EMPTY){
        G->value[x][y] = V_REACHABLE;
        MarkReachableAreas(G, x-1, y);
        MarkReachableAreas(G, x+1, y);
        MarkReachableAreas(G, x, y-1);
        MarkReachableAreas(G, x, y+1);
    }
}


void NumberTackleWithOthersAreas(grid * G, int x_area1, int y_area1){

}


void ProgressPath(grid * G, int x, int y) {



}

int InitWingerPosition(grid * G, int * x, int * y) {

}

void AddWinger(grid * G, int x, int y) {
    G->value[x][y] = V_WINGER;
}

void MoveWinger(grid * G, int x, int y){

}

void FindPath(grid * G) {

}

int main (void) {
    int width, height;
    scanf("%d", &width);
    scanf("%d", &height);

    grid G = InitGrid(width, height);
    // AddWinger(&G, 1, height/2 + height%2);


    int __nb_opposants__;
    scanf("%d", &__nb_opposants__);
    int __tackle_range__;
    scanf("%d", &__tackle_range__);

    for(int i = 0; i < __nb_opposants__; i++){
        int enemy_x, enemy_y;
        scanf("%d", &enemy_x);
        scanf("%d", &enemy_y);

        AddEnemy(&G, enemy_x, enemy_y, __tackle_range__);
    }

    for(int y = 1; y < G.Y; y++){
        MarkReachableAreas(&G, 1, y);
    }

    PrintGrid(G);
    // printf("%d\n", res);

    // FreeGrid(&G);


    return EXIT_SUCCESS;
}