#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <bits/stdc++.h> 

using namespace std;


#define NB_MOVES 4


typedef struct {
  int x,y;
} position;

typedef struct {
  int value;
  int mark;
  position pos_in_grid;
} node;

typedef struct {
  int width, height;
  node ** board;
} grid;

enum {
  V_WALL,        // empty cell
  V_GROUND,
  V_MARKED,
  V_EXIT
};

void PrintGrid(grid G) {
    for(int y = 0; y < G.height; y++) {
        for(int x = 0; x < G.width; x++){
            // if(G.value[x][y] == 4) printf("x ");
            // else if(G.value[x][y] == 3) printf("# ");
            // else if(G.value[x][y] == 2) printf("@ ");
            // else if(G.value[x][y] == 1) printf("* ");
            // else if(G.value[x][y] == 0) printf("- ");
            // else 
            if(G.board[x][y].mark == V_EXIT)  printf("%d_", G.board[x][y].value);
            else if( G.board[x][y].value > 0 && G.board[x][y].mark != V_EXIT) printf("%d ", G.board[x][y].value);
            else printf("x ");
        }
        printf("\n");
    }
    printf("* Width: %d\n* Height: %d\n", G.width, G.height);
}


grid AllocGrid(int width, int height) {
  grid G;
  G.width = width;
  G.height = height;

  G.board = (node **) malloc(width * sizeof(*(G.board)));

  for(int x = 0; x < width; x++) {
    G.board[x] = (node *) malloc(height * sizeof(* G.board[x]));

    for(int y = 0; y < height; y++) {
      G.board[x][y].mark  = V_WALL;
      G.board[x][y].value = -1;
      G.board[x][y].pos_in_grid.x = x;
      G.board[x][y].pos_in_grid.y = y;
    }
  }

  // G.board[width-1][height-1].mark = V_EXIT;
  return G;
}

grid InitGrid(int size) {
  grid map = AllocGrid(size, size);


  for(int y = 1; y < map.height-1; y++){
    string line;
    getline(cin, line);
    stringstream myString(line);
    for(int x = 1; x < map.width-1; x++){
      int type = -1;
      myString >> type;
      map.board[x][y].mark = V_GROUND;
      map.board[x][y].value = type;
      map.board[x][y].pos_in_grid.x = x;
      map.board[x][y].pos_in_grid.y = y;
    }

  }

  return map;
}

position* GetNeighbors(grid * G, int x, int y) {
  position *res = (position *) malloc(sizeof(position) * 5);

  res[0].x = x+1;
  res[0].y = y;

  res[1].x = x;
  res[1].y = y+1;

  res[2].x = x-1;
  res[2].y = y;

  res[3].x = x;
  res[3].y = y-1;

  res[4].x = 0x0;

  return res;
}

int FindPath(grid * G, int x, int y, int value, int best_value) {

  if(G->board[x][y].mark == V_WALL) return -1;
  if(x == G->width-1 && y == G->height-1)
    return value;
  value += G->board[x][y].value;
  printf("Exploring Position (%d,%d):%d\n", x, y, value);

  position * valid_moves = GetNeighbors(G, x, y);

  for(int i = 0; i < NB_MOVES; i++) {
    int new_x = valid_moves[i].x;
    int new_y = valid_moves[i].y;

    if(G->board[new_x][new_y].mark == V_WALL || G->board[new_x][new_y].mark == V_MARKED) continue;

    int current_value = FindPath(G, new_x, new_y, value, best_value);
    if(current_value > 0 && current_value < best_value) best_value = current_value;
  }
  G->board[x][y].mark = V_MARKED;


  return best_value;
}
int FindPath_wrapper(grid * G, int x, int y, int value, int best_value) {
  queue<node> q;
  q.push(G->board[x][y]);
  G->board[x][y].mark = V_MARKED;

  while (!q.empty()){
    node p = q.front();
    q.pop();

    if(p.pos_in_grid.x == G->width-2 && p.pos_in_grid.y == G->height-2){
      //END
      
    }
  }

    // res = FindPath(&G, 1, 1, 0, 99999);

}





int main() {
  int size = 3;
  // scanf("%d", &size);
  // if(size == 0) return 0;
  grid G = InitGrid(size+2);
  int res = 0;//G.board[1][1].value;

  PrintGrid(G);

  res = FindPath_wrapper(&G, 1, 1, 0, 99999);

  printf("Find a path of size: %d\n", res);
  return 0;
}