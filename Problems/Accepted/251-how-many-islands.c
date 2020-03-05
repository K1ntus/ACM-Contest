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
    V_WATER,    // Eau
    V_ISLAND,     // Sable
    V_WALL,
    // pour .mark
    M_MARKED,  // sommet non marqué
    M_UNMARKED,  // sommet marqué dans P
    M_NULL
};


//
// Alloue une grille aux dimensions x,y ainsi que son image. On force
// x,y>=3 pour avoir au moins un point qui n'est pas sur le bord.
//
static grid AllocGrid(int x, int y) {
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
        G.mark[i][j]  = M_NULL; // initialise
        G.value[i][j] = V_WALL;
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
            printf("%d ", G.value[x][y]);
        }
        printf("\n");
    }
    printf("* Width: %d\n* Height: %d\n", G.X, G.Y);
}

grid InitGrid(int width, int height) {
    grid G = AllocGrid(width+2, height+2);

    for(int y = 1; y < height + 1; y++){
        for(int x = 1; x < width + 1; x++){
            int value;
            scanf("%d", &value);
            // G.mark[x][y] = M_UNMARKED;
            switch(value) {
                case 0:
                    G.value[x][y] = V_WATER;
                    break;
                case 1:
                    G.value[x][y] = V_ISLAND;
                    G.mark[x][y] = M_UNMARKED;
                    break;
                default:
                    G.value[x][y] = V_WALL;
                    break;
            }

        }
    }

    return G;
}


/**
 * 
1 0 1 1 0 
1 0 0 1 1 
0 1 0 0 1 
0 1 0 1 1 
1 0 1 0 0 
 *
 */
void MarkNeighboursCells(grid * G, int x_init, int y_init) {
    if(G->mark[x_init][y_init] == M_MARKED) return;

    if(G->value[x_init][y_init] == V_WATER || G->value[x_init][y_init] == V_WALL) return;
    
    G->mark[x_init][y_init] = M_MARKED;

    MarkNeighboursCells(G, x_init-1, y_init);
    MarkNeighboursCells(G, x_init+1, y_init);

    MarkNeighboursCells(G, x_init, y_init-1);
    MarkNeighboursCells(G, x_init, y_init+1);

    MarkNeighboursCells(G, x_init+1, y_init-1);
    MarkNeighboursCells(G, x_init+1, y_init+1);

    MarkNeighboursCells(G, x_init-1, y_init-1);
    MarkNeighboursCells(G, x_init-1, y_init+1);    
}


int ExploreMap(grid * G) {
    int number_of_islands = 0;
    for(int y = 1; y < G->Y; y++) {
        for(int x = 1; x < G->X; x++) {
            // printf("Iteration (%d;%d)\n", x, y);
            if(G->mark[x][y] == M_MARKED) continue;

            if(G->value[x][y] == V_ISLAND && G->mark[x][y] == M_UNMARKED) {
                // printf("New island spotted from pos (%d,%d)!\n", x, y);
                if(!G->value[x][y] || !G || !G->value[x])
                    continue;
                // G->mark[x][y] = M_MARKED;
                MarkNeighboursCells(G, x, y);
                number_of_islands +=1;
            }
        }
    }

    return number_of_islands;
}

int main (void) {
    int width  = -1;
    int height = -1;
    while(width != 0 && height != 0){
        scanf("%d", &width);
        scanf("%d", &height);
        
        if(width == 0 && width == height) break;
        grid G = InitGrid(width, height);
        
        int res = ExploreMap(&G);
        printf("%d\n", res);


    }

    return EXIT_SUCCESS;
}