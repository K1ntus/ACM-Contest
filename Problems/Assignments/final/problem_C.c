// C / C++ program for Dijkstra's shortest path algorithm for adjacency 
// list representation of graph 


#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h>
#include <string.h>
#include <bits/stdc++.h> 
using namespace std; 


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
}; 

struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, int cost, int distance);
void removeEdge(struct Graph * graph, int node);

int * ShortestPathFromSrcToAll(struct Graph * graph, int src);
int * Dijkstra(struct Graph* graph, int src);

void printGraph(struct Graph * graph);




// Driver code 
int main() {
  
// This code is contributed by rathbhupendra 

    fprintf(stderr, "Running Problem C...\n");
    int __nb_cases__;
    string line;
    getline(cin, line);
    stringstream ss(line);
    ss >> __nb_cases__;
    

    for(int case_nb = 0; case_nb < __nb_cases__; case_nb++){
        int __nb_stations, __nb_segments;
        getline(cin,line);
        stringstream sstream(line);
        sstream >> __nb_stations >> __nb_segments;
        // fprintf(stdout, "Creating fraph with %d stations and %d segments\n", __nb_stations, __nb_segments);

        struct Graph * graph = createGraph(__nb_stations);

        for(int segment_id = 0; segment_id < __nb_segments ; segment_id++) {
            int src, dst, distance, cost;
            string line_input;
            getline(cin, line_input);

            stringstream sstream(line_input);
            sstream >> src >> dst >> distance >> cost;
            src = src - 1;
            dst = dst - 1;
            addEdge(graph, src, dst, cost, distance);
        }
  
  
        ShortestPathFromSrcToAll(graph, 0);
    }

	return 0; 
} 


int * ShortestPathFromSrcToAll(struct Graph * graph, int src) {

	//#ifdef __ONLY_POSITIVE_WEIGHT__ // 1
		return Dijkstra(graph, src);
	// #endif
	// #ifndef __ONLY_POSITIVE_WEIGHT__ // 1
	// BellmanFord(graph, src);
	// #endif // 0
	
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
    int distance;
	struct AdjListNode* next; 
}; 

// A structure to represent an adjacency list 
struct AdjList { 
	struct AdjListNode *head;
}; 


// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest, int cost, int distance) { 
	struct AdjListNode* newNode = 
			(struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	newNode->weight = cost;
    newNode->distance = distance; 
	newNode->next = NULL; 
	return newNode; 
} 

// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int size) { 
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->V = size; 

	graph->array = (struct AdjList*) malloc(size * sizeof(struct AdjList)); 

	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < size; ++i) 
		graph->array[i].head = NULL; 

	return graph; 
} 

// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest, int cost, int distance) { 
	// Add an edge from src to dest. A new node is added to the adjacency 
	// list of src. The node is added at the beginning 
	struct AdjListNode* newNode = newAdjListNode(dest, cost, distance); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode; 

	// Since graph is undirected, add an edge from dest to src also 
    //Comment the whole bloc if directed
	#ifdef __UNDIRECTED__
		newNode = newAdjListNode(src, cost, distance); 
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

// Structure to represent a min heap node 
struct MinHeapNode { 
	int v; 
	int dist; 
}; 

// Structure to represent a min heap 
struct MinHeap { 
	int size;	 // Number of heap nodes present currently 
	int capacity; // Capacity of min heap 
	int *pos;	 // This is needed for decreaseKey() 
	struct MinHeapNode **array; 
}; 

// A utility function to create a new Min Heap Node 
struct MinHeapNode* newMinHeapNode(int v, int dist) { 
	struct MinHeapNode* minHeapNode = 
		(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode)); 
	minHeapNode->v = v; 
	minHeapNode->dist = dist; 
	return minHeapNode; 
} 

// A utility function to create a Min Heap 
struct MinHeap* createMinHeap(int capacity) { 
	struct MinHeap* minHeap = 
		(struct MinHeap*) malloc(sizeof(struct MinHeap)); 
	minHeap->pos = (int *)malloc(capacity * sizeof(int)); 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = 
		(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

// A utility function to swap two nodes of min heap. Needed for min heapify 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) { 
	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// A standard function to heapify at given idx 
// This function also updates position of nodes when they are swapped. 
// Position is needed for decreaseKey() 
void minHeapify(struct MinHeap* minHeap, int idx) { 
	int smallest, left, right; 
	smallest = idx; 
	left = 2 * idx + 1; 
	right = 2 * idx + 2; 

	if (left < minHeap->size && 
		minHeap->array[left]->dist < minHeap->array[smallest]->dist ) 
	smallest = left; 

	if (right < minHeap->size && 
		minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
	smallest = right; 

	if (smallest != idx) 
	{ 
		// The nodes to be swapped in min heap 
		MinHeapNode *smallestNode = minHeap->array[smallest]; 
		MinHeapNode *idxNode = minHeap->array[idx]; 

		// Swap positions 
		minHeap->pos[smallestNode->v] = idx; 
		minHeap->pos[idxNode->v] = smallest; 

		// Swap nodes 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 

		minHeapify(minHeap, smallest); 
	} 
} 

// A utility function to check if the given minHeap is ampty or not 
int isEmpty(struct MinHeap* minHeap) { 
	return minHeap->size == 0; 
} 

// Standard function to extract minimum node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) { 
	if (isEmpty(minHeap)) 
		return NULL; 

	// Store the root node 
	struct MinHeapNode* root = minHeap->array[0]; 

	// Replace root node with last node 
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
	minHeap->array[0] = lastNode; 

	// Update position of last node 
	minHeap->pos[root->v] = minHeap->size-1; 
	minHeap->pos[lastNode->v] = 0; 

	// Reduce heap size and heapify root 
	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return root; 
} 


// Function to decreasy dist value of a given vertex v. This function 
// uses pos[] of min heap to get the current index of node in min heap 
void decreaseKey(struct MinHeap* minHeap, int v, int dist) { 
	// Get the index of v in heap array 
	int i = minHeap->pos[v]; 

	// Get the node and update its dist value 
	minHeap->array[i]->dist = dist; 

	// Travel up while the complete tree is not hepified. 
	// This is a O(Logn) loop 
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
	{ 
		// Swap this node with its parent 
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 

		// move to parent index 
		i = (i - 1) / 2; 
	} 
} 

// A utility function to check if a given vertex 
// 'v' is in min heap or not 
bool isInMinHeap(struct MinHeap *minHeap, int v) { 
	if (minHeap->pos[v] < minHeap->size) 
		return true; 
	return false; 
} 

// A utility function used to print the solution 
void printArr(int dist[], int cost[], int n) { 
    printf("%d %d\n", dist[n-1], cost[n-1]);
} 

// The main function that calulates distances of shortest paths from src to all 
// vertices. It is a O(ELogV) function 
int * Dijkstra(struct Graph* graph, int src) { 
	int V = graph->V;// Get the number of vertices in graph 
	int * cost = (int *) malloc(sizeof(int) * V);	 // dist values used to pick minimum weight edge in cut 
    int * dist = (int *) malloc(sizeof(int) * V);
	// minHeap represents set E 
	struct MinHeap* minHeap = createMinHeap(V); 

	// Initialize min heap with all vertices. dist value of all vertices 
	for (int v = 0; v < V; ++v) 
	{ 
		cost[v] = __INFINITY__;
        dist[v] = __INFINITY__; 
		minHeap->array[v] = newMinHeapNode(v, dist[v]); 
		minHeap->pos[v] = v; 
	} 

	// Make dist value of src vertex as 0 so that it is extracted first 
	minHeap->array[src] = newMinHeapNode(src, dist[src]); 
	minHeap->pos[src] = src; 
	dist[src] = 0; 
    cost[src] = 0;
	decreaseKey(minHeap, src, dist[src]); 

	// Initially size of min heap is equal to V 
	minHeap->size = V; 

	// In the followin loop, min heap contains all nodes 
	// whose shortest distance is not yet finalized. 
	while (!isEmpty(minHeap)) 
	{ 
		// Extract the vertex with minimum distance value 
		struct MinHeapNode* minHeapNode = extractMin(minHeap); 
		int u = minHeapNode->v; // Store the extracted vertex number 

		// Traverse through all adjacent vertices of u (the extracted 
		// vertex) and update their distance values 
		struct AdjListNode* pCrawl = graph->array[u].head; 
		while (pCrawl != NULL) 
		{ 
			int v = pCrawl->dest; 

			// If shortest distance to v is not finalized yet, and distance to v 
			// through u is less than its previously calculated distance 
			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
										pCrawl->distance + dist[u] < dist[v]) 
			{ 
				cost[v] = cost[u] + pCrawl->weight; 
                dist[v] = dist[u] + pCrawl->distance;

				// update distance value in min heap also 
				decreaseKey(minHeap, v, dist[v]); 
			} else if(dist[u] != INT_MAX && pCrawl->distance + dist[u] == dist[v]) {   //Same distance
                int tmp = cost[u] + pCrawl->weight;
                if(tmp < cost[v]) {
                    cost[v] = tmp;
                }
            }
			pCrawl = pCrawl->next; 
		} 
	} 

	// print the calculated shortest distances 
	printArr(dist, cost, V); 
	return dist;
} 



