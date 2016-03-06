//
//  main.cpp
//  5
//
//  Created by RYWU on 12/30/15.
//  Copyright (c) 2015 吳瑞洋公司. All rights reserved.
//
/*
 Problem Desc:
 Solution Desc:
 Ref:
 Sample In: 3 3 2 1 2 2 3 2 3 1 3 3 3 1 2 2 3 3 1 1 3 3 2 1 2 3 3 1 1 2 3 3 2 2 2 3 1 1 3
 Sample Out: 1 3 2 1 2 3 2 1 3
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>    // std::next_permutation, std::sort
#define MAX_NODE_NUM 1002
using namespace std;
int n = 0, m = 0;
int adj_matrix1[MAX_NODE_NUM][MAX_NODE_NUM] = {{0}};
int adj_matrix2[MAX_NODE_NUM][MAX_NODE_NUM] = {{0}};
int degree_of_graph1[MAX_NODE_NUM] = {0};
int degree_of_graph2[MAX_NODE_NUM] = {0};
int self_loop_of_graph1[MAX_NODE_NUM] = {0};
int self_loop_of_graph2[MAX_NODE_NUM] = {0};
int stop_flag = 0;

struct node {
    int info;
    node *next;
};

class Queue {
private:
    node *front;
    node *rear;
public:
    Queue();
    ~Queue();
    bool isEmpty();
    void enqueue(int);
    int dequeue();
    void display();
    
};

void Queue::display(){
    node *p = new node;
    p = front;
    if(front == NULL){
        cout<<"\nNothing to Display\n";
    }else{
        while(p!=NULL){
            cout<<endl<<p->info;
            p = p->next;
        }
    }
}

Queue::Queue() {
    front = NULL;
    rear = NULL;
}

Queue::~Queue() {
    delete front;
}

void Queue::enqueue(int data) {
    node *temp = new node();
    temp->info = data;
    temp->next = NULL;
    if(front == NULL){
        front = temp;
    }else{
        rear->next = temp;
    }
    rear = temp;
}

int Queue::dequeue() {
    node *temp = new node();
    int value;
    if(front == NULL){
        cout<<"\nQueue is Emtpty\n";
    }else{
        temp = front;
        value = temp->info;
        front = front->next;
        delete temp;
    }
    return value;
}

bool Queue::isEmpty() {
    return (front == NULL);
}

#include <vector>
vector<int> degree_g1;
vector<int> degree_g2;
vector<int> self_g1;
vector<int> self_g2;

void BFS(int s, int matrix[1002][1002], int n, int graph_1_2) {
    Queue Q;
    
    /** Keeps track of explored vertices */
    bool *explored = new bool[n+1];
    
    /** Initailized all vertices as unexplored */
    for (int i = 1; i <= n; ++i)
        explored[i] = false;
    
    /** Push initial vertex to the queue */
    Q.enqueue(s);
    explored[s] = true; /** mark it as explored */
//    cout << "Breadth first Search starting from vertex ";
//    cout << s << " : " << endl;
    
    /** Unless the queue is empty */
    while (!Q.isEmpty()) {
        /** Pop the vertex from the queue */
        int v = Q.dequeue();
        
        /** display the explored vertices */
//        cout << v << " ";
        if (graph_1_2 == 1){
            degree_g1.push_back(degree_of_graph1[v-1]);
            self_g1.push_back(self_loop_of_graph1[v-1]);
        }else{
            degree_g2.push_back(degree_of_graph2[v-1]);
            self_g2.push_back(self_loop_of_graph2[v-1]);
        }

        /** From the explored vertex v try to explore all the
         connected vertices */
        for (int w = 1; w <= n; ++w)
            
        /** Explores the vertex w if it is connected to v
         and and if it is unexplored */
            if (matrix[v-1][w-1] == 1 && !explored[w]) {
                /** adds the vertex w to the queue */
                Q.enqueue(w);
                /** marks the vertex w as visited */
                explored[w] = true;
            }
    }
//    cout << endl;
    delete [] explored;
}

int isPlagiarism(int permutation[MAX_NODE_NUM]){
    /*
     This function calculate whether given permutation data is a valid transform from adjM1 to adjM2.
     @param (int[]) permutation: the permutation array.
     @param (int) n: Number of nodes.
     @param (int) m: Number of edges.
     @return (int): 1 if a valid transformation, otherwise, 0.
     */
    
    for (int i = 0; i < n; i++) {
        if ( degree_of_graph1[i] != degree_of_graph2[permutation[i]-1] ||
            self_loop_of_graph1[i] != self_loop_of_graph2[permutation[i]-1])
        { // Not isomorphism.
            return 0;
        }
    }// else, Yes.
    return 1;
}

void p(int select[], int size1, int remain[], int size2){
    /*
     This function is the recursive function of permutation.
     @param (int[]) select: the number already been chosen.
     @param (int) size1: size of select[].
     @param (int[]) remain: the number to be chosen.
     @return (int) size2: size of remain[].
     */
    if (stop_flag == 1) {return;}
    if (size1 == n) {
        // print select[]
        if (isPlagiarism(select)) { for (int i = 0;i < size1; i++) {printf("%d ", select[i]);} printf("\n"); stop_flag = 1;}
        return;
    }
    
    int tmp[MAX_NODE_NUM] = {0};
    for (int i = 0; i < size2; i++) {
        if (stop_flag == 1) {break;}
        if (degree_of_graph1[size1] != degree_of_graph2[remain[i]-1] || self_loop_of_graph1[size1] != self_loop_of_graph2[remain[i]-1]) {continue;}
        // 每一點 往下跑 BFS
//        printf("size %d\n", size1);
//        printf("select[size1]+1: %d\n", select[size1]+1);
//        printf("select[remain[i]-1]+1: %d\n", select[remain[i]-1]+1);
        BFS(size1+1, adj_matrix1, n, 1);
        BFS(remain[i], adj_matrix2, n, 2);
        
        int stop = 0;
//        for (int i = 0; i < degree_g1.size(); i++) {
//            printf("%d %d\n", degree_g1[i], degree_g2[i]);
//        }
        for (int i = 0; i < degree_g1.size(); i++) {
            if (degree_g1[i] != degree_g2[i]) {stop = 1; }//printf("stop1\n");
        }
        for (int i = 0; i < self_g1.size(); i++) {
            if (self_g1[i] != self_g2[i]) {stop = 1;} //printf("stop2\n");
        }
        degree_g1.clear();degree_g2.clear();
        self_g1.clear();self_g2.clear();
        if (stop == 1){continue;}
        
        select[size1] = remain[i];
        int count = 0;
        for (int j = 0; j < size2; j++) {
            if (i != j){tmp[count] = remain[j]; count++;}
        }
        p(select, size1+1, tmp, size2-1);
    }
}

int Plagiarism(int adj_matrix1[MAX_NODE_NUM][MAX_NODE_NUM], int adj_matrix2[MAX_NODE_NUM][MAX_NODE_NUM]);
int main(int argc, const char * argv[]) {
    int t = 0;
    scanf("%d", &t);
    
    while (t--) { // Run T cases.
        scanf("%d %d", &n, &m);
        /* Initialize all global variables. */
        memset(degree_of_graph1, 0, sizeof(degree_of_graph1));
        memset(degree_of_graph2, 0, sizeof(degree_of_graph2));
        memset(self_loop_of_graph1, 0, sizeof(self_loop_of_graph1));
        memset(self_loop_of_graph2, 0, sizeof(self_loop_of_graph2));
        stop_flag = 0;
        
        for (int i = 0; i < n; i++) { // Initialize two adj_matrixs to 0;
            for (int j = 0; j < n; j++) {
                adj_matrix1[i][j] = 0;
                adj_matrix2[i][j] = 0;
            }
        }
        int a = 0, b = 0;
        for (int i = 0; i < m; i++) { // Read in Graph1 in adj_matrix1.
            scanf("%d %d", &a, &b);
            adj_matrix1[a-1][b-1] = 1;
            adj_matrix1[b-1][a-1] = 1;
            if (a == b) { self_loop_of_graph1[a-1]++;} // Self_loop.
            else { // Degree.
                degree_of_graph1[a-1]++;
                degree_of_graph1[b-1]++;
            }
        }
        for (int i = 0; i < m; i++) { // Read in Graph2 in adj_matrix2.
            scanf("%d %d", &a, &b);
            adj_matrix2[a-1][b-1] = 1;
            adj_matrix2[b-1][a-1] = 1;
            if (a == b) { self_loop_of_graph2[a-1]++;} // Self_loop.
            else { // Degree.
                degree_of_graph2[a-1]++;
                degree_of_graph2[b-1]++;
            }
        }
        Plagiarism(adj_matrix1, adj_matrix2);
    }
    
    return 0;
}
int Plagiarism(int adj_matrix1[MAX_NODE_NUM][MAX_NODE_NUM], int adj_matrix2[MAX_NODE_NUM][MAX_NODE_NUM]){
    /*
     This function calculate .
     @param (int) n: Number of nodes.
     @param (int) m: Number of edges.
     @param (int[][]) adj_matrix1: Adjacency matrix1 to represent the graph.
     @param (int[][]) adj_matrix2: Adjacency matrix2 to represent the graph.
     @return (int): 0, Print out the Permutation.
     */
    
    int select[MAX_NODE_NUM] = {0};
    int remain[MAX_NODE_NUM] = {0};
    for (int i = 0; i < n; i++) {remain[i] = i+1;}
    
    p(select, 0, remain, n);
    
    return 0;
}
