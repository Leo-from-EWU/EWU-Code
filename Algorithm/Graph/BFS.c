#include <stdio.h>
#include <stdlib.h>


#define MAX 100
#define WHITE 0 //white = unvisted
#define GRAY 1  //visited
#define BLACK 2 // visited & completed
int n;
int adj[MAX][MAX];

int color[MAX];
int distance[MAX];
int prev[MAX];  // Parent checking. 
// like 0,1,3 is connected and
//  we chose 2 no parent then went to 3 ,1 is parent.




void BFS(int s){
    int queue[MAX];
    int front=0,rear=0;
    
    for(int i=0;i<n;i++){
    if(i!=s){
        color[i]=WHITE;
        distance[i]=-1;
        prev[i]=-1;

    }}

    color[s]=GRAY;
    distance[s]=0;
    prev[s]=-1;
    queue[rear++]=s;

    while(front<rear){
        int u= queue[front++]; //1
        for(int v=0;v<n;v++){
            if(adj[u][v]==1 && color[v]==WHITE){
                color[v]=GRAY;
                distance[v]=distance[u]+1;
                prev[v]=u;
                queue[rear++]=v;
            }
        }
        color[u]=BLACK;

    }


    
}

int main(){
    int e;
    printf("Enter the vertices of the array: \n");
    scanf("%d",&n);
    

    printf("Enter the egdes of the array: \n");
    scanf("%d",&e);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j]=0;

        }
    }

    for(int i=0;i<e;i++){
        int u,v;
        printf("Enter the edges of (u,v): ");
        scanf("%d %d",&u,&v);
        adj[u][v]=1;
        adj[v][u]=1;

    }
    int s;
    printf("Enter the source :\n ");
    scanf("%d",&s);
    BFS(s);

    printf("\nVertex\tDistance\tPrevious\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", i, distance[i], prev[i]);
    }

    return 0;


}