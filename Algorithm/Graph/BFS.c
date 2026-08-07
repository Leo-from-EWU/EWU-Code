#include <stdio.h>
#include <stdlib.h>
#define m 100


// This BFS introduced for directed and wighted graph also

# define w 0 //White = unvisted
#define g 1 // Gary visited
#define b 2// Black visited & completed

int n;
int adj[m][m];
int color[m];
int parent[m];
int distance[m];

void BFS(int s){
    int que[m]; // queue
    int front=0, rear=0;

    for(int i=0;i<n;i++){
        if(s!=i){
            color[i]=w;
            distance[i]=-1;
            parent[i]=-1;
        }
        else{
            color[s]=g;
            distance[s]=0;
            parent[s]=-1;
            que[rear]=s;
            rear=rear+1;
        }
        }

        while (front<rear)
        {
            int u= que[front];
            front= front+1;
            for(int v=0;v<n;v++){
                if(adj[u][v]!=0 && color[v]==w){
                    color[v]=g;
                    distance[v]=distance[u]+1;
                    parent[v]=u;
                    que[rear]=v;
                    rear++;
                }
            }
            color[u]=b;
        }
        




    }


    



int main(){
    int e;
    printf("Enter the num of vertices: ");
    scanf("%d",&n);
    

    printf("Enter the egdes: (u,v)\n ");
    
    
    for(int u=0;u<n;u++){
        for(int v=0;v<n;v++){
        scanf("%d", &adj[u][v]);
        }
    }
    printf("Enter the source: ");
    scanf("%d",&e);
    BFS(e);

    printf("\nVertex\tdistance\tparent");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t\t%d\n",i,distance[i],parent[i]);
    }

}

