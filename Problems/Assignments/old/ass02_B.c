#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define __GUARD_RANGE__  100
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


double DistanceWithCell(int p_x, int p_y, position guard) {

    return sqrt( pow((guard.x - p_x), 2) + pow((guard.y - p_y), 2));
}


/* Function to print an array */
void printArray(position *arr, int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("(%d,%d) ", arr[i].x, arr[i].y); 
    printf("\n"); 
} 
void swap(position *xp, position *yp) 
{ 
    position temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void BubbleSort(position *arr, int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j].x > arr[j+1].x) 
              swap(&arr[j], &arr[j+1]); 
} 

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

bool MarkReachableAreas(grid * G, int x, int y, position*guards, int nb_guards){
    if(!(x > 0 && x < G->X && y > 0 && y < G->Y)) return false;

    if(G->value[x][y] == V_TACKLED || G->value[x][y] == V_WALL || G->value[x][y] == V_REACHABLE){
        return false;
    }
    
    bool res = false;
    
    for(int g_id = 0; g_id < nb_guards; g_id++){

        if((DistanceWithCell(x, y, guards[g_id]) < 100)) continue;
        if(G->value[x][y] == V_EMPTY){
            G->value[x][y] = V_REACHABLE;

            res = res || MarkReachableAreas(G, x-1, y, guards, nb_guards);
            res = res || MarkReachableAreas(G, x+1, y, guards, nb_guards);
            res = res || MarkReachableAreas(G, x, y-1, guards, nb_guards);
            res = res || MarkReachableAreas(G, x, y+1, guards, nb_guards);
        }

    }
    if(y == G->Y-2) return true;
    return res;
}



int main (void) {
    int width, height, __nb_opposants__;
    scanf("%d", &width);
    scanf("%d", &height);
    scanf("%d", &__nb_opposants__);

    printf("Init map of size (%d,%d) with %d guards\n", width, height, __nb_opposants__);

    position * guard_list = (position *) malloc(sizeof(position) * __nb_opposants__);

    grid map = InitGrid(width, height);
    for(int i = 0; i < __nb_opposants__; i++){
        int enemy_x, enemy_y;
        scanf("%d", &enemy_x);
        scanf("%d", &enemy_y);
        guard_list[i] = {enemy_x, enemy_y};
    }

    BubbleSort(guard_list, __nb_opposants__);

    int nb_guard = 0;
    bool reachable = false;
    int x_to_test = 1;
    while(!reachable && nb_guard < __nb_opposants__+2){
        for(int y = 1; y < map.Y; y++){
            reachable = MarkReachableAreas(&map, x_to_test, y, guard_list, __nb_opposants__ - nb_guard);

            if(reachable) {
                printf("%d\n", nb_guard);
            }
        }

        x_to_test = guard_list[0].x;
        for (int i = 0; i < __nb_opposants__ - nb_guard; i++) {
            guard_list[i] = guard_list[i + 1];
        }
        // printf("Guard list:\n");
        // printArray(guard_list, __nb_opposants__ - nb_guard);
        nb_guard+=1;
    }

    // FreeGrid(&map);
    return EXIT_SUCCESS;
}