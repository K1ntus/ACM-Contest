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
#define __SRC_NAME__ "office\0"
#define __DST_NAME__ "hall\0"


// #define __DIRECTED__
#define __ONLY_POSITIVE_WEIGHT__
#define __MAX_NB_CHAR_PLACE__ 18




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
void addEdge(struct Graph* graph, int src, int dest, int weight);
void removeEdge(struct Graph * graph, int node);

int * ShortestPathFromSrcToAll(struct Graph * graph, int src);
int * Dijkstra(struct Graph* graph, int src);
int * BellmanFord(struct Graph* graph, int src);

void printGraph(struct Graph * graph);


struct place {
    char* name;
    int id;
};


int getPlaceId(char** array, int nb_place, char* place){
    for(int i = 0; i < nb_place; i++) {
        if(strcmp(array[i], place) == 0){
            return i;
        }
    }
    return -1;
}

void printPlaceArray(char** array, int size) {
    printf("Place Array:\n");
    for(int i = 0; i < size; i++) {
        printf("\t[%d] %s\n", i, array[i]);
    }
}

int getPosSubstringPresent(char** array, int size, string str, int * place_id_found) {
    for(int i = 0; i < size; ++i) {
        int res = str.find(array[i]);   //Return first pos found
        if(res >= 0) {
            *place_id_found = i;
            return res;
        }
    }

    *place_id_found = 0;
    return -1;
}

void eraseSubStr(std::string & mainStr, const std::string & toErase)
{
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);
 
	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}

int main() { 


    while(!cin.eof()) {
        int __nb_places;
        int __nb_path;

        string line;
        getline(cin, line);
        stringstream nbpl(line);
        nbpl >> __nb_places;

        struct Graph* graph = createGraph(__nb_places);

        char ** place_list = (char**) malloc(sizeof(char*)*__nb_places);
        
        int src_id, dest_id;
        for(int place_id = 0; place_id < __nb_places; place_id++) {
            string line_place;
            getline(cin, line_place);

            place_list[place_id] = (char*) malloc(sizeof(char) * __MAX_NB_CHAR_PLACE__);

            strcpy(place_list[place_id], line_place.c_str());

            if(strcmp(__SRC_NAME__, place_list[place_id]) == 0) {
                src_id = place_id;
            } else if(strcmp(__DST_NAME__, place_list[place_id]) == 0) {
                dest_id = place_id;
            }

        }
        printPlaceArray(place_list, __nb_places);









        getline(cin, line);
        stringstream nbpath(line);
        nbpath >> __nb_path;

        for(int path_id = 0; path_id < __nb_path; ++path_id) {
            getline(cin, line);
            line = line + " 0";
            string token;
            istringstream ss(line);

            // getline(ss, token, '\0');
            // token.erase( remove_if(  token.begin(), token.end(), [](unsigned char x) {return std::isspace(x);}) , token.end() );
            
            int src_id, dst_id;
            int src_pos_input = getPosSubstringPresent(place_list, __nb_places, token, &src_id);
            int dst_pos_input = getPosSubstringPresent(place_list, __nb_places, token, &dst_id);
            // token.erase(0, dst_pos_input - 1); 
            string dst_str;
            dst_str.append(place_list[dst_id]);
            // dst_str(place_list[dst_id], __MAX_NB_CHAR_PLACE__);
            // eraseSubStr(token, dst_str);

            // int cost_from_src, cost_from_dst;
            // token >> cost_from_src, cost_from_dst;


            // printf("New roa/ from (%s,%d) to (%s,%d)\n", place_list[src_id], src_id, place_list[dst_str], dst_id);

        }

        // for(int path_id = 0; path_id < __nb_path; ++path_id) {
        //     getline(cin, line);
        //     string token;
        //     istringstream ss(line);
        //     stringstream blabla(line);
        //     char* caca;
        //     blabla >> caca;

        //     int edge_src, edge_dst;
        //     for(int i = 0; i < 2; ++i){
        //         getline(ss, token, ':');
        //         char* place_name;
        //         place_name << token << endl;

        //         int pos = getPlaceId(place_list, __nb_places, place_name);
        //         if(i == 0) { edge_src = pos; }
        //         else { edge_dst = pos; }
        //     }

        //     int cost_src_to_dst;
        //     int cost_dst_to_src;

        //     // getline(ss, token, ' ');
        //      cost_src_to_dst << blabla ;
        //     addEdge(graph, edge_src, edge_dst, cost_src_to_dst);

        // }

    }
	// struct Graph* graph = createGraph(__GRAPH_SIZE__); 
	// //A
	// addEdge(graph, 0, 1, 3);
	// addEdge(graph, 0, 2, 4);

	// //B
	// addEdge(graph, 1, 3, 8);
	// addEdge(graph, 1, 4, 7);

	// //C
	// addEdge(graph, 2, 4, 8);
	// addEdge(graph, 2, 5, 9);

	// //D
	// addEdge(graph, 3, 4, 1);
	// addEdge(graph, 3, 6, 6);

	// //E
	// addEdge(graph, 4, 5, 2);
	// addEdge(graph, 4, 6, 4);
	// addEdge(graph, 4, 7, 5);

	// //F
	// addEdge(graph, 5, 7, 2);

	// //G
	// addEdge(graph, 6, 8, 2);

	// //H
	// addEdge(graph, 7, 8, 3);

	
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

	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < size; ++i) 
		graph->array[i].head = NULL; 

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

