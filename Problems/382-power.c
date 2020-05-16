
// C++ program for implementation of Ford Fulkerson algorithm 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h>
#include <string.h>
#include <bits/stdc++.h> 
using namespace std; 

#define __INFINITY__ INT_MAX
/* Returns true if there is a path from source 's' to sink 't' in 
  residual graph. Also fills parent[] to store the path */
bool bfs(int **rGraph, int V, int s, int t, int parent[]) 
{ 
    // Create a visited array and mark all vertices as not visited 
    bool visited[V]; 
    memset(visited, 0, sizeof(visited)); 
  
    // Create a queue, enqueue source vertex and mark source vertex 
    // as visited 
    queue <int> q; 
    q.push(s); 
    visited[s] = true; 
    parent[s] = -1; 
  
    // Standard BFS Loop 
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop(); 
  
        for (int v=0; v<V; v++) 
        { 
            if (visited[v]==false && rGraph[u][v] > 0) 
            { 
                q.push(v); 
                parent[v] = u; 
                visited[v] = true; 
            } 
        } 
    } 
  
    // If we reached sink in BFS starting from source, then return 
    // true, else false 
    return (visited[t] == true); 
} 
  
// Returns the maximum flow from s to t in the given graph 
int fordFulkerson(int ** graph, int V, int s, int t) 
{ 
    int u, v; 
  
    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
    int **rGraph = (int **) malloc(sizeof(int* )* V);; // Residual graph where rGraph[i][j] indicates  
                     // residual capacity of edge from i to j (if there 
                     // is an edge. If rGraph[i][j] is 0, then there is not)   
    for (u = 0; u < V; u++) {
        rGraph[u] = (int *) malloc(sizeof(int) * V);
        for (v = 0; v < V; v++) 
             rGraph[u][v] = graph[u][v]; 
  
    }

    int parent[V];  // This array is filled by BFS and to store path 
  
    int max_flow = 0;  // There is no flow initially 
  
    // Augment the flow while tere is path from source to sink 
    while (bfs(rGraph, V, s, t, parent)) 
    { 
        // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        int path_flow = INT_MAX; 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = min(path_flow, rGraph[u][v]); 
        } 
  
        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 
  
        // Add path flow to overall flow 
        max_flow += path_flow; 
    } 
  
    // Return the overall flow 
    return max_flow; 
} 
  
// Driver program to test above functions 
int main() 
{ 

    while(!cin.eof()) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        int __nb_regulators;
        ss >> __nb_regulators;
        // __nb_regulators +=2;

        int **graph = (int **) malloc(sizeof(int*) * __nb_regulators);
        for(int i = 0; i < __nb_regulators; i++) {
            graph[i] = (int *) malloc(sizeof(int) * __nb_regulators);
            for(int j = 0; j < __nb_regulators; j++) {
                graph[i][j] = 0;
            }
        }
        graph[0][__nb_regulators] = __INFINITY__;
        
        getline(cin, line);
        // Regulators value

        

        getline(cin, line);
        stringstream ss1(line);
        int __nb_edges;
        ss1 >> __nb_edges;  
        for(int edge_id = 0; edge_id < __nb_edges; edge_id++) {
            int _src, _dst, _link_capacity;
            getline(cin, line);
            stringstream ss(line);
            ss >> _src >> _dst >> _link_capacity;

            graph[_src-1][_dst-1] = _link_capacity;
        }


        getline(cin, line);
        stringstream ss2(line);
        int __nb_input_regulators, __nb_output_regulators;
        ss2 >> __nb_input_regulators >> __nb_output_regulators;
        getline(cin, line);
        stringstream ss3(line);
        for(int i = 0; i < __nb_input_regulators; i++) {
            int _current_value;
            ss3 >> _current_value;

            graph[__nb_regulators-1][_current_value-1] = __INFINITY__;

        }

        for(int i = 0; i < __nb_output_regulators; i++) {
            int _current_value;
            ss3 >> _current_value;

            graph[_current_value - 1][__nb_regulators] = __INFINITY__;
        }
    cout << "The maximum possible flow is ";
    cout << fordFulkerson(graph, __nb_regulators, 0, __nb_regulators - 1);
    cout << endl; 
  

    }


    // // Let us create a graph shown in the above example 
    // int graph[V][V] = { {0, 16, 13, 0, 0, 0}, 
    //                     {0, 0, 10, 12, 0, 0}, 
    //                     {0, 4, 0, 0, 14, 0}, 
    //                     {0, 0, 9, 0, 0, 20}, 
    //                     {0, 0, 0, 7, 0, 4}, 
    //                     {0, 0, 0, 0, 0, 0} 
    //                   }; 
  
    // cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5); 
  
    return 0; 
} 
