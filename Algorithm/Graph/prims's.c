#include <stdio.h>
#include <stdlib.h>

#define m 100
int graph[m][m];
int n;
int total=0;
int cycle=0;

void prims(){
    int key[m];
    int tree[m];
    int parent[m];
    
    

    for(int i=0;i<n;i++){
        key[i]=999;
        tree[i]=0;
        parent[i]=-1;

    }
    key[0]=0;

    for(int i=0;i<n-1;i++){
        int u=-1,max=999;
        for(int v=0;v<n;v++){
            if(tree[v]==0 && key[v]<max){
                max=key[v];
                u=v;
            }
            
        }
        if(u==-1){
            printf("No Spanning Tree\n");
            return;}

        tree[u]=1;

        for(int v=0;v<n;v++){
            if(graph[u][v]!=0 && tree[v]==0 && graph[u][v]<key[v]){
                key[v]=graph[u][v];
                parent[v]=u;
            }
            else if(graph[u][v]!=0 && v!=u && v!=parent[u]){
                cycle=1;
            }
        }
    }

    printf("\nVertex\tKey\tParent\n");

for(int i = 0; i < n; i++){
    printf("%d\t%d\t%d\n", i, key[i], parent[i]);
    total+=key[i];
}
    printf("Total MST weight = %d\n", total);

    if(cycle)
        printf("Graph contains a cycle\n");
    else
        printf("Graph has no cycle (it is a tree)\n");
}


int main(){
     printf("entert how many vertices: \n");
    scanf("%d",&n);

    printf("entert edges: \n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&graph[i][j]);
        }
    }

    prims();

}