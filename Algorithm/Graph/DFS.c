#include <stdio.h>
#include <stdlib.h>

#define m 100
#define w 0
#define g 1
#define b 2

int n;
int graph[m][m];
int color[m];
int parent[m];
int distance[m];
int f[m];
int time=0;
int cycle=0;
int s[m];

void dfs_visit(int u){
    color[u]=g;
    time=time+1;
    distance[u]=time;
    s[u]=time;

    for(int v=0;v<n;v++){
        if(graph[u][v]!=0){
            if(color[v]==w){
                parent[v]=u;
                dfs_visit(v);
            }
            else if(v!=parent[u]){
                cycle=1;
            }
        }
        
    }
    color[u]=b;
    time++;
    f[u]=time;
}

void DFS(){
    for(int i=0;i<n;i++){
        color[i]=w;
        distance[i]=-1;
        parent[i]=-1;

    }
    time=0;
    cycle=0;

    for(int u=0;u<n;u++){
        if(color[u]==w){
            dfs_visit(u);
        }
    }
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
    
    DFS();

    printf("\nVertex\tdistance\tparent\tfinishting time\tstarting time\n");
    for(int i=0;i<n;i++){
    printf("%d\t%d\t\t%d\t%d\t\t%d\n",i,distance[i],parent[i],f[i],s[i]);
    }

    if (cycle == 1)

        printf("\nCycle detected!\n");

    else

        printf("\nNo cycle detected.\n");

}