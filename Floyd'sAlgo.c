#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 99999

void printMatrix(int **dist, int V) {
    printf("\nShortest distance matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", dist[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int **graph, int V) {
    int i, j, k;

    // Allocate dist matrix
    int **dist = (int **)malloc(V * sizeof(int *));
    for (i = 0; i < V; i++)
        dist[i] = (int *)malloc(V * sizeof(int));

    // Copy graph to dist
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Algorithm
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printMatrix(dist, V);

    // Free memory
    for (i = 0; i < V; i++)
        free(dist[i]);
    free(dist);
}

int main() {
    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    // Allocate graph
    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        graph[i] = (int *)malloc(V * sizeof(int));

    srand(time(0)); // seed random

    // Generate random graph
    printf("\nGenerated Graph:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j)
                graph[i][j] = 0;
            else {
                int r = rand() % 10;

                // Randomly assign INF (no edge)
                if (r < 3)
                    graph[i][j] = INF;
                else
                    graph[i][j] = r + 1;
            }

            if (graph[i][j] == INF)
                printf("INF ");
            else
                printf("%3d ", graph[i][j]);
        }
        printf("\n");
    }

    clock_t start, end;
    double time_taken;

    start = clock();

    floydWarshall(graph, V);

    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nExecution Time: %f seconds\n", time_taken);

    // Free graph
    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
