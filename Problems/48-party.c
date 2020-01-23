// http://acm.cs.cityu.edu.hk/oj2/index.php/p/438/getProblemStatement?act=view

// A C Program to demonstrate adjacency list  
// representation of graphs 
#include <stdio.h> 
#include <stdlib.h> 
  
#define SIZE 10000

// A structure to represent an adjacency list node 
struct AdjListNode 
{ 
    int dest; 
    struct AdjListNode* next; 
}; 
  
// A structure to represent an adjacency list 
struct AdjList 
{ 
    struct AdjListNode *head;  
}; 
  
// A structure to represent a graph. A graph 
// is an array of adjacency lists. 
// Size of array will be V (number of vertices  
// in graph) 
struct Graph 
{ 
    int V; 
    struct AdjList* array; 
}; 
  
// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest) 
{ 
    struct AdjListNode* newNode = 
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
    newNode->dest = dest; 
    newNode->next = NULL; 
    return newNode; 
} 

int sizeNode(struct Graph * G, int node){
    int res_size = -1;
        struct AdjListNode* pCrawl = G->array[node].head;
        if(pCrawl == 0x0)
            return -1; 
        while (pCrawl) 
        { 
            res_size++;
            pCrawl = pCrawl->next; 
        } 
        // if(res_size != -1)
        //     printf("\n Size of node %d: %d\n ", node, res_size); 
    return res_size;
}

int NumberOfNodes(struct Graph * G){
    int counter = 0;
    int v; 
    for (v = 0; v < G->V; ++v) 
    { 
        if(sizeNode(G, v) == -1) continue;
        struct AdjListNode* pCrawl = G->array[v].head; 
        if(pCrawl == NULL) continue;
        // printf("\n Adjacency list of vertex %d\n head ", v); 
        counter+=1;
        // printf("\n"); 
    } 
    return counter;
}
  
// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int V) 
{ 
    struct Graph* graph =  
        (struct Graph*) malloc(sizeof(struct Graph)); 
    graph->V = V; 
  
    // Create an array of adjacency lists.  Size of  
    // array will be V 
    graph->array =  
      (struct AdjList*) malloc(V * sizeof(struct AdjList)); 
  
    // Initialize each adjacency list as empty by  
    // making head as NULL 
    int i; 
    for (i = 0; i < V; ++i) 
        graph->array[i].head = NULL; 
  
    return graph; 
} 
  
void addNode(struct Graph * G){
    G->V += 1;

    G->array = (struct AdjList *) realloc(G->array, G->V * sizeof(struct  AdjList));

}



// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest) 
{ 
    // printf("Adding an end from node %d to %d\n", src, dest);
    // Add an edge from src to dest.  A new node is  
    // added to the adjacency list of src.  The node 
    // is added at the begining 
    struct AdjListNode* newNode = newAdjListNode(dest); 
    newNode->next = graph->array[src].head; 
    graph->array[src].head = newNode; 
  
    // Since graph is undirected, add an edge from 
    // dest to src also 
    newNode = newAdjListNode(src); 
    newNode->next = graph->array[dest].head; 
    graph->array[dest].head = newNode; 
} 

void removeEdge(struct Graph * graph, struct AdjListNode* node){

}
// A utility function to print the adjacency list  
// representation of graph 
void printGraph(struct Graph* graph) 
{ 
    int v; 
    for (v = 0; v < graph->V; ++v) 
    { 
        struct AdjListNode* pCrawl = graph->array[v].head; 
        if(pCrawl == NULL) continue;
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
} 
  
// Driver program to test above functions 
int main() 
{ 
    // create the graph given in above fugure 
    int number_of_people = 0;
    // fprintf(stderr, "Number of tests to run: ");
    scanf("%d", &number_of_people);
    // fprintf(stderr, "There will be %d Tests Case.\n", number_of_people);

    struct Graph* graph = createGraph(SIZE); 
    

    //Init graph
    for(int i = 0; i < number_of_people; i++){
        char * tmp_buffer = (char *) malloc(sizeof(char) * SIZE);
        int number_of_friends = 0;
        scanf("%d", &number_of_friends);

 
        for(int dest = 0; dest < number_of_friends; dest++){
            if(dest < graph->V)
                addNode(graph);
            addEdge(graph, dest, i);
        }
        free(tmp_buffer);
    }

    int min = SIZE;
    for(int j = graph->V; j>0 && number_of_people > 0; j--) {
        for(int i = 0; i < SIZE; i++){
            
            int node_size = sizeNode(graph, i);

            if(node_size == -1){    //Unlinked node
                graph->array[i].head = NULL;
            }else if(node_size < min){
                min = node_size;
            }
        }

        for(int i = 0; i < SIZE; i++){
            int node_size = sizeNode(graph, i);
            if(node_size <= min && graph->array[i].head != NULL){
                graph->array[i].head = NULL;
                graph->V -=1;
                // j -=1;
                // printf("Removed a node.\n");
            }
        }

    }

        fprintf(stdin, "%d\n", NumberOfNodes(graph));

    // addEdge(graph, 0, 1); 
    // addEdge(graph, 0, 4); 
    // addEdge(graph, 1, 2); 
    // addEdge(graph, 1, 3); 
    // addEdge(graph, 1, 4); 
    // addEdge(graph, 2, 3); 
    // addEdge(graph, 3, 4); 
  
    // print the adjacency list representation of the above graph 
    // printGraph(graph); 
  
    return 0; 
} 
