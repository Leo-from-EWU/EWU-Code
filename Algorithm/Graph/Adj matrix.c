#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0, e;
    printf("Enter the number of vertices :");
    scanf("%d", &n);
    printf("Enter the number of edges :");
    scanf("%d", &e);

    int adj[n][n];

    // Input
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < e; i++)
    {
        int u, v;
        printf("Enter the edges: %d (u),(v) :\n", i + 1);
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    printf("\nAdjacency Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}