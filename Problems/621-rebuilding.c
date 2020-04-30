
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


Graph* createGraph(int V, int E);
int KruskalMST(Graph* graph);

#define __INFINITY__ INT_MAX

// Driver code 
int main()  
{  
    /* Let us create following weighted graph  
            10  
        0--------1  
        | \ |  
    6| 5\ |15  
        | \ |  
        2--------3  
            4 */
    int V; // Number of cities/Vertices
    string line;
    getline(cin, line);
    stringstream myString(line);
    myString >> V;



    while(V != 0) {

        Graph* graph = createGraph(V, V*V*V);  
    
        int __nb_edge = 0;
        for(int y = 0; y < V; y++) {
            getline(cin, line);
            stringstream myString(line);

            for(int x = 0; x < V; x++) {
                char current_state;
                myString >> current_state;

                graph->edge[__nb_edge].src = y;
                graph->edge[__nb_edge].dest = x;
                graph->edge[__nb_edge].weight = __INFINITY__;

                if (current_state == '1') {  //Road already built
                    // printf("-- Adding existing edge: %d->%d\n", y, x);
                    graph->edge[__nb_edge].weight = 0;
                }
                __nb_edge += 1;
            }
        }
        // printf("Existing (and not) roads. Current nb edges: %d\n", __nb_edge);


        for(int y = 0; y < V; y++) {
            getline(cin, line);
            stringstream myString(line);

            for(int x = 0; x < V; x++) {
                // if(x == y) { continue; }    // Same edge
                int __cost_for_creation;

                myString >> __cost_for_creation;
                graph->edge[__nb_edge].src = y;
                graph->edge[__nb_edge].dest = x;
                graph->edge[__nb_edge].weight = __cost_for_creation;

                __nb_edge += 1;

                // printf("-- Possible road creation (%d,%d):%d\n",y,x,__cost_for_creation);

            }
        }




        for(int y = 0; y < V; y++) {
            getline(cin, line);
            stringstream myString(line);

            for(int x = 0; x < V; x++) {
                // if(x == y) { continue; }    // Same edge
                int __cost_for_deletion;

                myString >> __cost_for_deletion;
                graph->edge[__nb_edge].src = y;
                graph->edge[__nb_edge].dest = x;
                graph->edge[__nb_edge].weight = __cost_for_deletion;

                // printf("-- Possible road deletion (%d,%d):%d\n",y,x,__cost_for_deletion);

                __nb_edge += 1;

            }
        } 
    
        int res = KruskalMST(graph);  
  
        printf("---- RES: %d\n", res);

        getline(cin, line);
        stringstream myString(line);
        myString >> V;

    }
    return 0;  
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
int KruskalMST(Graph* graph)  
{  
    int V = graph->V;  
    Edge result[V]; // Tnis will store the resultant MST  
    int e = 0; // An index variable, used for result[]  
    int i = 0; // An index variable, used for sorted edges  
  
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
    cout<<"Following are the edges in the constructed MST\n";  
    int res = 0;
    for (i = 0; i < e; ++i)  {
        cout<<result[i].src<<" -- "<<result[i].dest<<" == "<<result[i].weight<<endl;  
        res += result[i].weight;
    }
    return res;  
}  