//
//  main.cpp
//  4
//
//  Created by RYWU on 12/7/15.
//  Copyright (c) 2015 吳瑞洋公司. All rights reserved.
//
/*
 Problem Desc: Find all the possible minimum spanning tree's mutual edge.
 Solution Desc: Use Kruskal algorithm, hide every edge in MST, then do the hidden-edged grapg with kruskal again.
 Ref: http://www.geeksforgeeks.org/greedy-algorithms-set-2-kruskals-minimum-spanning-tree-mst/
 Example In: 3 3 3 1 2 3 2 3 3 3 1 2 3 3 1 2 3 2 3 3 3 1 3 3 3 1 2 3 2 3 3 3 1 4
 Example Out: 1 2 0 0 2 6
 */
#define MAX_NODE_NUM 50001
#define MAX_EDGE_NUM 1000001
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm> // In Kruskal: sort().
using namespace std;

// a structure to represent a weighted edge in graph
struct Edge
{
    int src, dest, weight;
};

// a structure to represent a connected, undirected and weighted graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
    
    // graph is represented as an array of edges. Since the graph is
    // undirected, the edge from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    struct Edge* edge;
};


/*
 Global variable:
 mst_result:
 input_edge:
 mst_edge_num:
 */
struct Edge input_edge[MAX_EDGE_NUM];  // This will store the input edges.
struct Edge mst_result[MAX_NODE_NUM];  // Tnis will store the result MST.
struct Edge first_mst_result[MAX_NODE_NUM];  // Tnis will store the MST we do the first time.
int first_mst_edge_count = 0;
int mst_edge_count = 0;
int input_edge_count = 0;
int input_vertex_count = 0;
long long correct_mst_weight_sum = 0;
int skip_at_this_index = 2147483647;


// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
    
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
    
    return graph;
}

// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i (path compression)
    
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    
    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    
    // If ranks are same, then make one as root and increment
    // its rank by one
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
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph)
{
    int V = graph->V;
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges
    
    
    // Allocate memory for creating V ssubsets
    struct subset *subsets =
    (struct subset*) malloc( V * sizeof(struct subset) );
    
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    // Number of edges to be taken is equal to V-1
    while (e < V - 1)
    {
        // Catch the margin: if the index overflow, just break the loop.
        if (i == graph->E){
//            printf("e = %d, i = %d\n", e, i);
//            printf("break while: CANNOT FORM A MST.\n");
            break;
        }
        
        // Skip at this index, for rerun Kruskal purpose.
        if (i == skip_at_this_index){
            i++;
            continue;
        }
        
        // Step 2: Pick the smallest edge. And increment the index
        // for next iteration
        struct Edge next_edge = graph->edge[i++];
        
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        
        // If including this edge does't cause cycle, include it
        // in result and increment the index of result for next edge
        if (x != y)
        {
            mst_result[e] = next_edge;
            e++;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
    mst_edge_count = e;
    
    return;
}

int must_edge(int n, int m){
    /*
     This function calculate the number of must_edge and the sum of its weight.
     @param (int) n: Number of nodes.
     @param (int) m: Number of edges.
     @param (int**) adj_matrix: Adjacency matrix to represent the graph.
     @return (int): 0, Print out the number of must_edge and the sum of its weight.
     */
    correct_mst_weight_sum = 0;
    skip_at_this_index = 2147483647;
    int V = n;  // Number of vertices in graph
    int E = m;  // Number of edges in graph
    input_edge_count = m;
    input_vertex_count = n;
    
    struct Graph* graph = createGraph(V, E);
    
    for (int i = 0; i < m; i++) {
        graph->edge[i].src = input_edge[i].src;
        graph->edge[i].dest = input_edge[i].dest;
        graph->edge[i].weight = input_edge[i].weight;
    }
    
    // Kruskal Step 1:  Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
    
    KruskalMST(graph);
    
    int num_of_must_edge = 0;
    long long sum_weight_of_must_edge = 0;
    
//            printf("Input Starts: \n");
//            for (int i = 0; i < m; i++) {
//                printf("%d %d %d\n", input_edge[i].src, input_edge[i].dest, input_edge[i].weight);
//            }
    
    // Calculate the correct edge sum.
    for (int i = 0; i < mst_edge_count; i++) {
        correct_mst_weight_sum += mst_result[i].weight;
    }

    // Copy the MST we do the first time to first_mst_result.
    first_mst_edge_count = mst_edge_count;
    for (int i = 0; i < first_mst_edge_count; i++) {
        first_mst_result[i].src = mst_result[i].src;
        first_mst_result[i].dest = mst_result[i].dest;
        first_mst_result[i].weight = mst_result[i].weight;
    }

//    printf("first_mst_edge_count: \n");
//    for (int i = 0; i < first_mst_edge_count; i++) {
//        printf("%d - %d: %d\n", first_mst_result[i].src, first_mst_result[i].dest, first_mst_result[i].weight);
//    }
    
    
    // Find the must edge.
    for (int i = 0; i < input_vertex_count-1; i++) { // iterate through first_mst_result[].
        long long new_sum = 0;
        
        // Find the index of this edge in graph.
        for (int index = i; index < input_edge_count; index++) {
            if (first_mst_result[i].src == graph->edge[index].src && first_mst_result[i].dest == graph->edge[index].dest && first_mst_result[i].weight == graph->edge[index].weight)
            {
                skip_at_this_index = index;
                break;
            }
        }
        // Run Kruskal again to get the new_sum;
        KruskalMST(graph);
        
        // Re-calculate the new sum.
        for (int i = 0; i < mst_edge_count; i++) {
            new_sum += mst_result[i].weight;
        }
        
        if (new_sum != correct_mst_weight_sum){ // IS must edge.
//            printf("MUST edge: %d - %d: %d\n", first_mst_result[i].src, first_mst_result[i].dest, first_mst_result[i].weight);
            num_of_must_edge ++;
            sum_weight_of_must_edge += first_mst_result[i].weight;
        }
    }
    
    printf("%d %lld\n", num_of_must_edge, sum_weight_of_must_edge);
    
    return 0;
}

int main(int argc, const char * argv[]) {
    int T = 0;
    scanf("%d", &T);
    while (T--) {
        int n = 0, m = 0;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++){
            int a = 0, b = 0, weight = 0;
            scanf("%d %d %d", &a, &b, &weight);
            input_edge[i].src = a-1;
            input_edge[i].dest = b-1;
            input_edge[i].weight = weight;
            if (input_edge[i].src > input_edge[i].dest){
                int tmp = input_edge[i].src;
                input_edge[i].src = input_edge[i].dest;
                input_edge[i].dest = tmp;
            }
        }
        must_edge(n, m);
    }
    return 0;
}
