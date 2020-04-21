// C / C++ program for Dijkstra's shortest path algorithm for adjacency 
// list representation of graph 

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h>
#include <string.h>
#include <bits/stdc++.h> 
using namespace std; 

#define __GRAPH_SIZE__ 9
#define __INFINITY__ INT_MAX

// #define __DIRECTED__
#define __ONLY_POSITIVE_WEIGHT__





#ifndef __ONLY_POSITIVE_WEIGHT__
#define __NEGATIVE_WEIGHT__
#endif
#ifndef __DIRECTED__
#define __UNDIRECTED__
#endif



// A structure to represent a graph. A graph is an array of adjacency lists. 
// Size of array will be V (number of vertices in graph) 
struct Graph { 
	int V; 
	struct AdjList* array; 
    int * visited;
    int * skip;
}; 

struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, int weight);
void removeEdge(struct Graph * graph, int node);


void DFS(struct Graph* graph, int vertex);
int SizeComponent(struct Graph * graph);
void printGraph(struct Graph * graph);

// Source: https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/

int sumArray(int* arr, int n){
    int res = 0;
    for(int i = 0; i < n; i++){
        if(arr[i] != __INFINITY__){
            res += 1;
        }
    }
    return res;
}

bool skipAnalytic(struct Graph * graph, int id){
    if(graph->skip[id] == true){
        return true;
    }
    return false;
}

int main() { 


    int V; // Number of cities/Vertices
    int E; // Number of connections/Edges in graph  
    string line;
    getline(cin, line);
    stringstream myString(line);

    int __nb_case__ = 0;
    myString >> __nb_case__;

    for(int case_id = 0; case_id < __nb_case__; case_id++) {
        
        getline(cin, line);
        stringstream myString(line);
        int __nb_people__, __nb_connections__;
        myString >> __nb_people__ >> __nb_connections__;

        struct Graph* graph = createGraph(__nb_people__); 
        //fprintf(stdout, "Created graph of size: %d %d\n", __nb_people__, __nb_connections__);

        for(int i = 0; i < __nb_connections__; i++) {
            int src,dest;
			getline(cin, line);
			stringstream myString(line);
			myString >> src >> dest;

            addEdge(graph, src-1, dest-1, 1); 
            
        }

        // printGraph(graph);
        // fprintf(stdout, "*********\n");
        // removeEdge(graph, 6);
        // removeEdge(graph, 3);

        int min_value = -1;
        for(int i = 0; i < __nb_people__; i++){
            if(!skipAnalytic(graph, i)){
                int tmp = 0;
                DFS(graph, i);
                tmp = SizeComponent(graph);
                //int tmp = sumArray(Dijkstra(graph, i), __nb_people__); 
                //printf("Component size: %d\n", tmp);
                if( tmp > min_value) {
                    min_value = tmp;
                }
            }
        }
        

    	// getline(cin, line);
        printf("%d\n", min_value);
    }
	return 0; 
} 





int SizeComponent(struct Graph * graph){
    int count = 0;
    for(int i = 0; i < graph->V; i++){
        if(graph->visited[i]>0){
            count +=1;
            graph->skip[i] = 1;
        }
        graph->visited[i] = 0;
    }
    return count;
}















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
    bool visited;
	struct AdjListNode* next; 
}; 

// A structure to represent an adjacency list 
struct AdjList { 
	struct AdjListNode *head;
}; 


// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest, int weight) { 
	struct AdjListNode* newNode = 
			(struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	newNode->weight = weight; 
    newNode->visited = false;
	newNode->next = NULL; 
	return newNode; 
} 

// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int size) { 
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->V = size; 
    graph->visited = (int*) malloc(sizeof(int) * size);
    graph->skip = (int*) malloc(sizeof(int) * size);
	graph->array = (struct AdjList*) malloc(size * sizeof(struct AdjList)); 

    for(int i = 0; i < size; i++){
        graph->visited[i] = 0;
        graph->skip[i] = 0;
    }
    // Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < size; ++i) 
		graph->array[i].head = NULL; 

	return graph; 
} 

void UnmarkAllGraph(struct Graph * graph) {

    for(int vertices_id = 0; vertices_id < graph->V; vertices_id++) {
        
        struct AdjListNode* pCrawl = graph->array[vertices_id].head; 
        while (pCrawl) 
        { 
            pCrawl->visited = false;
            pCrawl = pCrawl->next; 
        } 
    }
}


// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest, int weight) { 
    //fprintf(stdout, "Added edge between %d and %d\n", src, dest);
	// Add an edge from src to dest. A new node is added to the adjacency 
	// list of src. The node is added at the beginning 
	struct AdjListNode* newNode = newAdjListNode(dest, weight); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode; 

	// Since graph is undirected, add an edge from dest to src also 
    //Comment the whole bloc if directed
	#ifdef __UNDIRECTED__
		newNode = newAdjListNode(src, weight); 
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


	graph->array[node_to_remove].head->weight = 999999;
	graph->array[node_to_remove].head->next = 0x0;
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



void DFS(struct Graph* graph, int vertex) {
        
        graph->visited[vertex] = 1;
        //printf("Visited %d \n", vertex);
    
        struct AdjListNode* pCrawl = graph->array[vertex].head; 
        while(pCrawl) {
            int connectedVertex = pCrawl->dest;
        
            if(graph->visited[connectedVertex] == 0) {
                DFS(graph, connectedVertex);
            }
            pCrawl = pCrawl->next; 
        }     

        /*   
        while (pCrawl) 
        { 
            pCrawl->visited = false;
            pCrawl = pCrawl->next; 
        } 
        */

          
}

