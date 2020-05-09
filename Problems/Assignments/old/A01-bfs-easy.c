// C / C++ program for Dijkstra's shortest path algorithm for adjacency 
// list representation of graph 

#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h>

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
}; 
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


struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, int weight);
void removeEdge(struct Graph * graph, int node);

int * ShortestPathFromSrcToAll(struct Graph * graph, int src);
int * Dijkstra(struct Graph* graph, int src);
int * BellmanFord(struct Graph* graph, int src);
void bfs(struct Graph* graph, int startVertex, int vertex_to_stop);

void printGraph(struct Graph * graph);

// Source: https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/


int NbRoadDestoyable(struct Graph * graph) {
	int sum = 0;
	int i = 0;
	for(; i < graph->V; i++){
		if(graph->array[i].head->visited)
			sum += 1;
	}

	return sum;
}
int main() { 
	int nb_cases = 0;
	scanf("%d", &nb_cases);

	fprintf(stderr, "There is %d cases.\n", nb_cases);

	for(int i = 0; i < nb_cases; i++) {
		int nb_cities = 0;
		int nb_edges = 0;

		scanf("%d", &nb_cities);

		scanf("%d", &nb_edges);
		fprintf(stderr, "Init graph with %d nodes and %d edges\n", nb_cities, nb_edges);
		struct Graph* graph = createGraph(nb_cities); 

		for(int current_edge = 0; current_edge < nb_edges; current_edge++) {
			int src = 0;
			int dst = 0;

			scanf("%d", &src);
			scanf("%d", &dst);

			addEdge(graph, src-1, dst-1, 1);
		}

		int SourceCity, TargetCity, MaxTroups;

		scanf("%d", &SourceCity);
		scanf("%d", &TargetCity);
		scanf("%d", &MaxTroups);

		fprintf(stderr, "S=%d, T=%d, L=%d\n", SourceCity, TargetCity, MaxTroups);

		bfs(graph, SourceCity-1, TargetCity-1);
		fprintf(stderr, "%d roads can be destroyed.\n", NbRoadDestoyable(graph));
	}


	// struct Graph* graph = createGraph(__GRAPH_SIZE__); 
	// // printGraph(graph);
	// // fprintf(stdout, "*********\n");
	// // removeEdge(graph, 6);
	// // removeEdge(graph, 3);

	// ShortestPathFromSrcToAll(graph, 0);

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









// A linked list (LL) node to store a queue entry 
struct QNode { 
    int key; 
    struct QNode* next; 
}; 
  
// The queue, front stores the front node of LL and tail stores the 
// last node of LL 
struct Queue { 
    struct QNode *front, *tail; 
	int size;
}; 
  
// A utility function to create a new linked list node. 
struct QNode* newNode(int k) 
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
void enQueue(struct Queue* q, int k) 
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
int deQueue(struct Queue* q) 
{ 
    // If queue is empty, return NULL. 
    if (q->front == NULL) 
        return -1; 
  
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

void bfs(struct Graph* graph, int startVertex, int vertex_to_stop) {

    struct Queue* q = createQueue(); 
    
    graph->array[startVertex].head->visited = true;
    enQueue(q, startVertex);
    
    while(q->front){
        // printQueue(q);
        int currentVertex = deQueue(q);
        // fprintf(stderr,"Visited %d\n", currentVertex);
    
		struct AdjList node_array = graph->array[currentVertex];
		// fprintf(stderr, "a\n");

		if(&node_array == 0x0) continue;
		struct AdjListNode * temp = node_array.head;

        while(temp) {
            int adjVertex = temp->dest;
			// fprintf(stderr, "read node %d. Value is %d\n", adjVertex, graph->visited[adjVertex]);

            if(graph->array[adjVertex].head->visited == false){
                graph->array[adjVertex].head->visited = true;
                enQueue(q, adjVertex);
				// fprintf(stderr,"Enqueued.\n");
            }else{
				// fprintf(stderr, "no enqueu\n");
			}

            temp = temp->next;
        }
		// fprintf(stderr, "b\n");
    }

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




// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int dest, int weight) { 
	struct AdjListNode* newNode = 
			(struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	newNode->weight = weight; 
	newNode->next = NULL; 
	return newNode; 
} 

// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int size) { 
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->V = size; 

	graph->array = (struct AdjList*) malloc(size * sizeof(struct AdjList)); 
	// graph->visited = (int *) malloc(sizeof(int) * size);
	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < size; ++i)  {
		graph->array[i].head = NULL; 
		// graph->visited[i] = 0;
	}

	return graph; 
} 

// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest, int weight) { 
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
void printArr(int dist[], int n) { 
	printf("Vertex Distance from Source\n"); 
	for (int i = 0; i < n; ++i) {
		if (dist[i] == __INFINITY__){
			printf("%d \t\t Unreachable\n", i, dist[i]); 
		} else {
			printf("%d \t\t %d\n", i, dist[i]); 
		}
	}
} 

// The main function that calulates distances of shortest paths from src to all 
// vertices. It is a O(ELogV) function 
int * Dijkstra(struct Graph* graph, int src) { 
	int V = graph->V;// Get the number of vertices in graph 
	int * dist = (int *) malloc(sizeof(int) * V);	 // dist values used to pick minimum weight edge in cut 

	// minHeap represents set E 
	struct MinHeap* minHeap = createMinHeap(V); 

	// Initialize min heap with all vertices. dist value of all vertices 
	for (int v = 0; v < V; ++v) 
	{ 
		dist[v] = __INFINITY__; 
		minHeap->array[v] = newMinHeapNode(v, dist[v]); 
		minHeap->pos[v] = v; 
	} 

	// Make dist value of src vertex as 0 so that it is extracted first 
	minHeap->array[src] = newMinHeapNode(src, dist[src]); 
	minHeap->pos[src] = src; 
	dist[src] = 0; 
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
										pCrawl->weight + dist[u] < dist[v]) 
			{ 
				dist[v] = dist[u] + pCrawl->weight; 

				// update distance value in min heap also 
				decreaseKey(minHeap, v, dist[v]); 
			} 
			pCrawl = pCrawl->next; 
		} 
	} 

	// print the calculated shortest distances 
	printArr(dist, V); 
	return dist;
} 



// The main function that finds shortest distances from src to all other
// vertices using Bellman-Ford algorithm.  The function also detects negative
// weight cycle
int * BellmanFord(struct Graph* graph, int src) {

    int V = graph->V;
    int * dist = (int *) malloc(sizeof(int) * V);

    int i,j;

    // Step 1: Initialize distances from src to all other vertices as INFINITE
    for (i = 0; i < V; i++)
        dist[i]   = __INFINITY__;
	struct AdjListNode * node = graph->array[0].head;
	while(node){
		dist[node->dest] = node->weight;
		node = node->next;
	}
	// free(node);
    dist[src] = 0;


    // Step 2: Relax all edges |V| - 1 times. A simple shortest path from src
    // to any other vertex can have at-most |V| - 1 edges
    for (i = 0; i < V; i++) {
		// printf("P\n");
		struct AdjListNode * node = graph->array[i].head;
		while(node && node->next) {
            int u = node->dest;
			if(dist[u] == __INFINITY__) {
				node = node->next;
				continue;
			}
            int v = node->next->dest;
            int weight = node->weight;

            if (dist[u] + weight < dist[v]) {
				printf("%d+%d -> %d for indice %d\n", dist[u], weight, dist[v], v);
                dist[v] = dist[u] + weight;
			}
			node = node->next;
        }

    }


    // Step 3: check for negative-weight cycles.  The above step guarantees
    // shortest distances if graph doesn't contain negative weight cycle. 
    // If we get a shorter path, then there is a cycle.
    for (i = 0; i < V; i++) {
		struct AdjListNode * node = graph->array[i].head;
		while(node->next) {
			int u = node->dest;
			int v = node->next->dest;
			int weight = node->weight;

			if (dist[u] + weight < dist[v]) {
            	printf("Graph contains negative weight cycle");
				break;
			}

			node = node->next;
		}
	}
    printArr(dist, V);
    return dist;

}

