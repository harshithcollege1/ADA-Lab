#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define INF 9999999

int main() {
    int V;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    // Allocate adjacency matrix
    int **G = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        G[i] = (int *)malloc(V * sizeof(int));
    }

    // Seed random generator
    srand(time(NULL));

    // Generate random graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                G[i][j] = 0;
            } else {
                int weight = rand() % 100 + 1; // weights 1–100
                G[i][j] = weight;
                G[j][i] = weight; // make it undirected
            }
        }
    }

    int *selected = (int *)calloc(V, sizeof(int));
    int no_edge = 0;

    selected[0] = true;

    int x, y;

    clock_t start = clock();

    printf("\nEdge : Weight\n");

    while (no_edge < V - 1) {
        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && G[i][j]) {
                        if (min > G[i][j]) {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        printf("%d - %d : %d\n", x, y, G[x][y]);

        selected[y] = true;
        no_edge++;
    }

    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nTime taken: %f seconds\n", time_taken);

    // Free memory
    for (int i = 0; i < V; i++) {
        free(G[i]);
    }
    free(G);
    free(selected);

    return 0;
}
