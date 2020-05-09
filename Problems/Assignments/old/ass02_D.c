
// C++ program for Kruskal's algorithm to find Minimum Spanning Tree  
// of a given connected, undirected and weighted graph  


// Arbre couvrant de poids minimum
// Tous les sommets relies par somme des aretes minimum
#include <bits/stdc++.h> 
using namespace std; 
  
// a structure to represent a weighted edge in graph  
class Edge  
{  
    public: 
    int src, dest, weight;  
};  


#define __NO_STATION_FOUND__ -1
#define __MAX_LENGTH_STATION_NAME__ 10
// a structure to represent a weighted edge in graph  
class Dictionnary  
{  
    public: 
    int size;
    int *id;
    char ** station;
};  
  
// a structure to represent a connected, undirected  
// and weighted graph  
class Graph  
{  
    public: 
    // V-> Number of vertices, E-> Number of edges  
    int V, E;  
  
    // graph is represented as an array of edges.  
    // Since the graph is undirected, the edge  
    // from src to dest is also edge from dest  
    // to src. Both are counted as 1 edge here.  
    Edge* edge;  
};  

void PrintGraph(Graph * graph) {
    printf("Graph:\n");
    for(int i = 0; i < graph->E; i++) {
        printf("(%d,%d,%d)\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }
}
  
// Creates a graph with V vertices and E edges  
Graph* createGraph(int V, int E)  
{  
    Graph* graph = new Graph;  
    graph->V = V;  
    graph->E = E;  
  
    graph->edge = new Edge[E];  
  
    return graph;  
}  
  
Dictionnary* initDict(int V) {
    Dictionnary * dict = new Dictionnary;
    dict->size = 0;
    dict->id = (int*) malloc(sizeof(int) * V);
    dict->station = (char**) malloc(sizeof(char*) * V);

    return dict;
}
// A structure to represent a subset for union-find  
class subset  
{  
    public: 
    int parent;  
    int rank;  
};  
  
// A utility function to find set of an element i  
// (uses path compression technique)  
int find(subset subsets[], int i)  
{  
    // find root and make root as parent of i  
    // (path compression)  
    if (subsets[i].parent != i)  
        subsets[i].parent = find(subsets, subsets[i].parent);  
  
    return subsets[i].parent;  
}  
  
// A function that does union of two sets of x and y  
// (uses union by rank)  
void Union(subset subsets[], int x, int y)  
{  
    int xroot = find(subsets, x);  
    int yroot = find(subsets, y);  
  
    // Attach smaller rank tree under root of high  
    // rank tree (Union by Rank)  
    if (subsets[xroot].rank < subsets[yroot].rank)  
        subsets[xroot].parent = yroot;  
    else if (subsets[xroot].rank > subsets[yroot].rank)  
        subsets[yroot].parent = xroot;  
  
    // If ranks are same, then make one as root and  
    // increment its rank by one  
    else
    {  
        subsets[yroot].parent = xroot;  
        subsets[xroot].rank++;  
    }  
}  
  
// Compare two edges according to their weights.  
// Used in qsort() for sorting an array of edges  
int myComp(const void* a, const void* b)  
{  
    Edge* a1 = (Edge*)a;  
    Edge* b1 = (Edge*)b;  
    return a1->weight > b1->weight;  
}  
  
// The main function to construct MST using Kruskal's algorithm  
void KruskalMST(Graph* graph)  
{  
    int V = graph->V;  
    Edge *result = (Edge*) malloc(sizeof(Edge) * V); // Tnis will store the resultant MST  
    int i = 0; // An index variable, used for sorted edges  
    int e = 0; // An index variable, used for result[]  
  
    // Step 1: Sort all the edges in non-decreasing  
    // order of their weight. If we are not allowed to  
    // change the given graph, we can create a copy of  
    // array of edges  
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);  
  
    // Allocate memory for creating V ssubsets  
    subset *subsets = new subset[( V * sizeof(subset) )];  
  
    // Create V subsets with single elements  
    for (int v = 0; v < V; ++v)  
    {  
        subsets[v].parent = v;  
        subsets[v].rank = 0;  
    }  
  
    // Number of edges to be taken is equal to V-1  
    while (e < V - 1 && i < graph->E)  
    {  
        // Step 2: Pick the smallest edge. And increment  
        // the index for next iteration  
        Edge next_edge = graph->edge[i++];  
  
        int x = find(subsets, next_edge.src);  
        int y = find(subsets, next_edge.dest);  
  
        // If including this edge does't cause cycle,  
        // include it in result and increment the index  
        // of result for next edge  
        if (x != y)  
        {  
            result[e++] = next_edge;  
            Union(subsets, x, y);  
        }  
        // Else discard the next_edge  
    }  
  
    // print the contents of result[] to display the  
    // built MST  

    if(e == graph->V-1) { // Tree is noice
        int value = 0;
        // cout<<"Following are the edges in the constructed MST\n";  
        
        for (i = 0; i < e; ++i)  {
            // cout<<result[i].src<<" -- "<<result[i].dest<<" == "<<result[i].weight<<endl;  
            value += result[i].weight;
        }
        printf("%d\n", value);
    } else {
        printf("Impossible\n");
    }

    return;
}  

void AddStation(char * stationName, Dictionnary * dict) {
    dict->station[dict->size] = stationName;
    dict->id[dict->size] = dict->size;
    // printf("-- Added Station: (%s,%d)\n", stationName, dict->size);
    dict->size += 1;
}

int StationNameToInteger(char * name, Dictionnary * dict) {
    for(int i = 0; i < dict->size; i++){
        if(strcmp(name, dict->station[i]) == 0) return i;
    }

    return __NO_STATION_FOUND__;
}

char* IntegerToStationName(int id, Dictionnary* dict) {
    return dict->station[id];
}
  
void PrintDictionnary (Dictionnary * dict) {
    printf("(Station, ID):\n");
    for(int i = 0; i < dict->size; i++) {
        printf("--- (%s,%d)\n", dict->station[i], dict->id[i]);
    }
}

// Driver code 
int main() {  
    /* Let us create following weighted graph  
            10  
        0--------1  
        | \ |  
    6| 5\ |15  
        | \ |  
        2--------3  
            4 */
    while(1){
        int V; // Number of stations/Vertices
        int E; // Number of connections/Edges in graph  
        string line;
        getline(cin, line);
        stringstream myString(line);
        myString >> V >> E;

        if(V == E && V == 0) { return EXIT_SUCCESS; }

        E = E * 2;

        Graph* graph = createGraph(V, E);  
        Dictionnary * dict = initDict(V);
    
        for(int edge_number = 0; edge_number < V; edge_number++) {
            char * station = (char*) malloc(sizeof(char) * __MAX_LENGTH_STATION_NAME__);

            getline(cin, line);
            stringstream myString(line);
            myString >> station;
            
            AddStation(station, dict);
        }


        for(int vertices_number = 0; vertices_number < E;){

            char * departure_station = (char*) malloc(sizeof(char) * __MAX_LENGTH_STATION_NAME__);
            char * destination_station = (char*) malloc(sizeof(char) * __MAX_LENGTH_STATION_NAME__);
            int cost = 0;

            getline(cin, line);
            stringstream myString(line);
            myString >> departure_station >> destination_station >> cost;

            // printf("Added vertice (%s,%s,%d)\n", departure_station, destination_station, cost);
            graph->edge[vertices_number].src = StationNameToInteger(departure_station, dict);
            graph->edge[vertices_number].dest = StationNameToInteger(destination_station, dict);
            graph->edge[vertices_number].weight = cost;

            // printf("Added vertice (%s,%s,%d)\n", destination_station, departure_station, cost);
            graph->edge[vertices_number+1].src = StationNameToInteger(destination_station, dict);
            graph->edge[vertices_number+1].dest = StationNameToInteger(departure_station, dict);
            graph->edge[vertices_number+1].weight = cost;

            vertices_number+=2;
        }

        getline(cin, line);
        stringstream myString2(line);
        char * initialStation = (char*) malloc(sizeof(char) * __MAX_LENGTH_STATION_NAME__);
        myString2 >> initialStation;
    
        int initial_node = StationNameToInteger(initialStation, dict);

        // PrintGraph(graph);
        // PrintDictionnary(dict);

        KruskalMST(graph);  
    }
    return 0;  
}  
  
// This code is contributed by rathbhupendra 
