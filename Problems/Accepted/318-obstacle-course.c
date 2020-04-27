#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define __MAX_NB_MOVES__ 4 //Max nb of moves per turn (top, bot, left, right)
#define __MAXIMUM_COST__ INT_MAX

// #define __INFINITY__ INT_MAX
#define __INFINITY__ INT_MAX


// Une position entière dans la grille.
typedef struct {
    int x, y;
} position;

// Une grille.
typedef struct {
    int X, Y;       // dimensions: X et Y
    int **value;    // valuation des cases: value[i][j], 0<=i<X, 0<=j<Y
    int **mark;     // marquage des cases: mark[i][j], 0<=i<X, 0<=j<Y
    int **cost;
} grid;

// Valeurs possibles des cases d'une grille pour les champs .value et
// .mark. L'ordre est important: il doit être cohérent avec les
// tableaux color[] (tools.c) et weight[] (a_star.c).
enum {

    // pour .value
    V_EMPTY,        // empty cell
    V_MARKED,     // queen
    V_VISITED,
    V_WALL          // game frontier
};


// A structure to represent a stack 
// A linked list (LL) node to store a queue entry 
struct QNode { 
    position key; 
    struct QNode* next; 
}; 
  
// The queue, front stores the front node of LL and tail stores the 
// last node of LL 
struct Queue { 
    struct QNode *front, *tail; 
	int size;
}; 
void enQueue(struct Queue* q, position k) ;
struct Queue* createQueue();
position deQueue(struct Queue* q);
int isEmptyQueue(struct Queue* pQueue);





  




grid InitGrid(int size);
void PrintGrid(grid G);

int MoveRover(grid * G, position current_position);


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

        int res = MoveRover(&G, {1,1});
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





int min(int a, int b) {
    if(a<b){
        return a;
    }
    return b;
}


position * getLegalMoves(grid * G, position p) {
    position * res = (position *) malloc(sizeof(position) * __MAX_NB_MOVES__);

    res[0]={p.x - 1, p.y};
    res[1]={p.x + 1, p.y};
    res[2]={p.x, p.y - 1};
    res[3]={p.x, p.y + 1};

    return res;
}

void addLegalMoves(grid * G, struct Queue * dataset, position current_pos) {

    if(G->mark[current_pos.x + 1][current_pos.y] == V_EMPTY) {
        enQueue(dataset, {current_pos.x + 1, current_pos.y});
    }
    if(G->mark[current_pos.x - 1][current_pos.y] == V_EMPTY) {
        enQueue(dataset, {current_pos.x - 1, current_pos.y});
    }
    if(G->mark[current_pos.x][current_pos.y + 1] == V_EMPTY) {
        enQueue(dataset, {current_pos.x, current_pos.y + 1});
    }
    if(G->mark[current_pos.x][current_pos.y - 1] == V_EMPTY) {
        enQueue(dataset, {current_pos.x, current_pos.y - 1});
    }

}







int MoveRover(grid * G, position current_position) {

    // Mark all nodes as unvisited with a distance from src to infinity

    struct Queue * moveQueue = createQueue();
    for(int x = 1; x < G->X - 1; ++x) {
        for(int y = 1; y < G->Y - 1; ++y) {
            G->mark[x][y] = V_EMPTY;
            G->cost[x][y] = __INFINITY__;
        }
    }
    G->cost[1][1] = G->value[1][1];
    G->mark[1][1] = V_VISITED;
    enQueue(moveQueue, {1,1});

    // addLegalMoves(G, moveQueue, {1,1});
    while(!isEmptyQueue(moveQueue)) {
        position current_position = deQueue(moveQueue);
        position * neighboard = getLegalMoves(G, current_position);


        for(int nb_id = 0; nb_id < __MAX_NB_MOVES__; ++nb_id) {
            // printf("New: %d\n", nb_id);
            position next_pos = neighboard[nb_id];
            int x,y;
            x = next_pos.x;
            y = next_pos.y;

            if(G->mark[x][y] != V_EMPTY) { continue; }

            int value = G->cost[current_position.x][current_position.y] + G->value[x][y];// + G->cost[current_position.x][current_position.y];
            // printf("NextVal: %d (%d+%d)\n", value, G->cost[current_position.x][current_position.y], G->value[next_pos.x][next_pos.y]);
            if(value < G->cost[x][y]) {
                // printf("Minimal value (%d,%d): %d->%d\n", next_pos.x, next_pos.y, G->cost[next_pos.x][next_pos.y], value);
                G->cost[x][y] = value;
                enQueue(moveQueue, next_pos);
            }
        }

        // G->mark[current_position.x][current_position.y] = V_VISITED;

    }

    // PrintGrid(*G);

    return G->cost[dest_pos][dest_pos];// + G->value[dest_pos][dest_pos];
}



/**
 * 
 * Take too much time, deprecated.
 */
int MoveRover_deprecated(grid * G, position current_position, int flow, int bestFlow) {
    int curr_x = current_position.x;
    int curr_y = current_position.y;

    // Update the current flow value
    flow = flow + G->value[curr_x][curr_y];     


    // If current pos is destination pos, return updated flow
    if(curr_x == dest_pos && curr_y == dest_pos) {
        return flow;
    }

    // If the flow is already greater than the bestFlow, return
    if(flow >= bestFlow - offset) {
        return __MAXIMUM_COST__;
    }

    // Get the four possibles legalMoves
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
        int val = __INFINITY__;
        // val = MoveRover(G, nextMove, flow, bestFlow);

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
    G.cost  = (int**) malloc(x * sizeof(*(G.mark)));

    for (int i = 0; i < x; ++i) {
        G.value[i] = (int*) malloc(y * sizeof(*(G.value[i])));
        G.mark[i]  = (int*) malloc(y * sizeof(*(G.mark[i])));
        G.cost[i]  = (int*) malloc(y * sizeof(*(G.cost[i])));

        if(G.mark[i] == 0x0 || G.value[i] == 0x0) {
            fprintf(stderr, "Unable to alloc memory.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < y; ++j) {
            G.value[i][j] = 126;
            G.mark[i][j] = V_WALL;
            G.cost[i][j] = __INFINITY__;
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
            if(G.mark[x][y] == V_WALL) printf("###");
            else if(G.mark[x][y] == V_EMPTY) printf("%3d ", G.cost[x][y]);
            else printf("%d ", G.cost[x][y]);
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

    G.cost[1][1] = G.value[1][1];

    return G;
}












/**
 * 
 * QUEUE
 * 
 */


// A utility function to create a new linked list node. 
struct QNode* newNode(position k) 
{ 
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode)); 
    temp->key = k; 
    temp->next = NULL; 
    return temp; 
} 
  
// A utility function to create an empty queue 
struct Queue* createQueue() 
{ 
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue)); 
    q->front = q->tail = NULL; 
	q->size = 0;
    return q; 
} 
  
// The function to add a key k to q 
void enQueue(struct Queue* q, position k) 
{ 
    // Create a new LL node 
    struct QNode* temp = newNode(k); 
  
    // If queue is empty, then new node is front and tail both 
    if (q->tail == NULL) { 
        q->tail = temp; 
		q->front = temp;
		q->size = 1;
        return; 
    } 
  
	q->size +=1;
    // Add the new node at the end of queue and change tail 
    q->tail->next = temp; 
    q->tail = temp; 
} 
  
// Function to remove a key from given queue q 
position deQueue(struct Queue* q) 
{ 
    // If queue is empty, return NULL. 
    if (q->front == NULL) 
        return {0,0}; 
  
    // Store previous front and move front one node ahead 
    struct QNode* temp = q->front; 
  
    q->front = q->front->next; 
  
    // If front becomes NULL, then change tail also as NULL 
    if (q->front == NULL) 
        q->tail = NULL; 
	
	q->size -=1;
    return temp->key;
} 

int isEmptyQueue(struct Queue* pQueue) {
    if (pQueue == NULL) {
        return false;
    }
    if (pQueue->size == 0) {
        return true;
    } else {
        return false;
    }
}
