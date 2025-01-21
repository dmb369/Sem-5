#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

// BFS Function
bool bfs(int graph[100][100], int nodes, int source, int sink, int parent[]) {
    bool visited[100] = {false}; 
    int queue[100], front = 0, rear = 0;

    queue[rear++] = source;
    visited[source] = true;
    parent[source] = -1;

    while (front < rear) {
        int current = queue[front++];
        for (int next = 0; next < nodes; next++) {
          
            if (!visited[next] && graph[current][next] > 0) {
                queue[rear++] = next;
                parent[next] = current;
                visited[next] = true;
                if (next == sink) {
                    return true; 
                }
            }
        }
    }
    return false;
}

// Ford-Fulkerson Algorithm
int calculate(int graph[100][100], int nodes, int source, int sink) {
    int residual[100][100];
    int parent[100];
    int maxFlow = 0;

    
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            residual[i][j] = graph[i][j];
        }
    }

   
    while (bfs(residual, nodes, source, sink, parent)) {
        int flow = INT_MAX;

        
        for (int node = sink; node != source; node = parent[node]) {
            int prev = parent[node];
            if (residual[prev][node] < flow) {
                flow = residual[prev][node];
            }
        }

        
        for (int node = sink; node != source; node = parent[node]) {
            int prev = parent[node];
            residual[prev][node] -= flow;
            residual[node][prev] += flow;
        }

        maxFlow += flow;
    }

    return maxFlow;
}

int main() {
    int nodes, edges;
    scanf("%d %d", &nodes, &edges);

    int graph[100][100] = {0}; 

    for (int i = 0; i < edges; i++) {
        int from, to, cap;
        scanf("%d %d %d", &from, &to, &cap);
        graph[from][to] = cap; 
    }

    int source, sink;
    scanf("%d %d", &source, &sink);

    printf("Maximum Flow: %d\n", calculate(graph, nodes, source, sink));

    return 0;
}
