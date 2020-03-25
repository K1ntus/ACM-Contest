// http://acm.cs.cityu.edu.hk/oj2/index.php/p/438/getProblemStatement?act=view

// A C Program to demonstrate adjacency list  
// representation of graphs 
#include <stdio.h> 
#include <limits.h> 
#include <stdlib.h> 
  
#define __SIZE__ 10000

#define __INFINITY__ INT_MAX

// #define __DIRECTED__
#define __ONLY_POSITIVE_WEIGHT__

#ifndef __ONLY_POSITIVE_WEIGHT__
#define __NEGATIVE_WEIGHT__
#endif
#ifndef __DIRECTED__
#define __UNDIRECTED__
#endif

// A structure to represent a graph. A graph 
// is an array of adjacency lists. 
// Size of array will be V (number of vertices  
// in graph) 
struct Graph 
{ 
    int V; 
    struct AdjList* array; 
}; 



/**
 * 
 *  Utility Function
 *       Graph
 *   Representation
 *        And
 *  Short-Path Algo
 * 
 */



// A structure to represent a node in adjacency list 
struct AdjListNode { 
	int dest; 
	int weight; 
	struct AdjListNode* next; 
}; 

// A structure to represent an adjacency list 
struct AdjList { 
	struct AdjListNode *head;
}; 


// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest) { 
	struct AdjListNode* newNode = 
			(struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	// newNode->weight = weight; 
	newNode->next = NULL; 
	return newNode; 
} 

// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int size) { 
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->V = size; 

	graph->array = (struct AdjList*) malloc(__SIZE__ * sizeof(struct AdjList)); 

	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < size; ++i) 
		graph->array[i].head = NULL; 

	return graph; 
} 

void AddNode(struct Graph* graph) {
    graph->V+=1;
	graph->array[graph->V-1].head = NULL; 
}

// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest) { 
	// Add an edge from src to dest. A new node is added to the adjacency 
	// list of src. The node is added at the beginning 
	struct AdjListNode* newNode = newAdjListNode(dest); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode; 

	// Since graph is undirected, add an edge from dest to src also 
    //Comment the whole bloc if directed
	#ifdef __UNDIRECTED__
		newNode = newAdjListNode(src); 
		newNode->next = graph->array[dest].head; 
		graph->array[dest].head = newNode; 
	#endif
} 

void removeEdge(struct Graph * graph, int node_to_remove) {
	for(int i = 0; i < graph->V; i++){
		struct AdjList node_array = graph->array[i];

		if(&node_array == 0x0) continue;
		struct AdjListNode * prev_node = node_array.head;
		// printf("Analyzing node %d\n", i);

		if(prev_node != 0x0) {
			if(prev_node->dest == node_to_remove) {
				graph->array[i].head = prev_node->next;
				prev_node = prev_node->next;
			}
		}

		while(prev_node != 0x0) {
			struct AdjListNode * current_node = prev_node->next;
			if(current_node == 0x0) break;

			if(current_node->dest == node_to_remove) {
				prev_node->next = current_node->next;
				// printf("Removed a node.\n");
			}

			prev_node = prev_node->next;
		}
	}


	// graph->array[node_to_remove].head->weight = __INFINITY__;
	graph->array[node_to_remove].head->next = 0x0;
}

void RemoveNode(struct Graph* graph, int node_to_remove){
    removeEdge(graph, node_to_remove);
    graph->array[node_to_remove].head = NULL;

    for(int i = node_to_remove+1; i < graph->V; i++){
        graph->array[i-1].head = graph->array[i].head;
    }
    graph->array[graph->V].head = NULL;
    graph->V -=1;


}

void printGraph(struct Graph* graph) { 
    int v; 
    for (v = 0; v < graph->V; ++v) 
    { 
        struct AdjListNode* pCrawl = graph->array[v].head; 
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
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

    for (v = 0; v < G->V; v++) { 

        // if(G->array[v].head) counter += 1;

        if(sizeNode(G, v) == -1) continue;
        struct AdjListNode* pCrawl = G->array[v].head; 
        if(pCrawl == NULL) continue;
        // printf("\n Adjacency list of vertex %d\n head ", v); 
        counter+=1;
        // printf("\n"); 
    } 
    return counter;
}





// Driver program to test above functions 
int main(void) { 
    // create the graph given in above fugure 
    int number_of_people = 0;
    // fprintf(stderr, "Number of tests to run: ");
    scanf("%d", &number_of_people);
    // fprintf(stderr, "There will be %d Tests Case.\n", number_of_people);

    struct Graph* graph = createGraph(1); 
    

    //Init graph
    for(int i = 0; i < number_of_people; i++){
        char * tmp_buffer = (char *) malloc(sizeof(char) * __SIZE__);
        int number_of_friends = 0;
        scanf("%d", &number_of_friends);

 
        for(int dest = 0; dest < number_of_friends; dest++){
            if(dest < graph->V)
                AddNode(graph);
            addEdge(graph, dest, i);
        }
        free(tmp_buffer);
    }

    printf("Current Graph While Partying:\n");
    printGraph(graph);

    int min = __SIZE__;
    for(int j = graph->V; j>0 && number_of_people > 0; j--) {
        for(int i = 0; i < graph->V; i++){
            
            int node_size = sizeNode(graph, i);

            if(node_size == -1){    //Unlinked node
                graph->array[i].head = NULL;
                // removeEdge(graph, i);
            }else if(node_size < min){
                min = node_size;
            }
        }

        for(int i = 0; i < graph->V; i++){
            int node_size = sizeNode(graph, i);
            if(node_size <= min && graph->array[i].head != NULL){
                RemoveNode(graph, i);

                // graph->array[i].head = NULL;
                // removeEdge(graph, i);
                // j -=1;
                // printf("Removed a node.\n");
            }
        }


    }

    fprintf(stdout, "%d\n", NumberOfNodes(graph), graph->V);

    free(graph);
  
    // print the adjacency list representation of the above graph 
    // printGraph(graph); 
  
    return 0; 
} 
