#include <stdio.h>

int max(int a,int b){
    if(a>b)
    return a;
    else
    return b;
}
int main(){
    int weight[]={0,2,1,3,2};
    int value[]={0,12,10,20,15};
    int capacity=5;

    int rows= sizeof(weight)/sizeof(weight[0]);
    int colums= capacity+1;

    int dp[rows][colums];

    for(int i=0;i<rows;i++){
        for(int w=0;w<colums;w++){
            if(i==0 || w==0)
            dp[i][w]=0;

            else if(weight[i]>w){
                dp[i][w]=dp[i-1][w];
            }
            else{
                int include= value[i]+dp[i-1][w-weight[i]];
                int exlude= dp[i-1][w];
                dp[i][w]=max(include,exlude);
            }
        }
    }

    int arr[rows];
    for (int k = 0; k < rows; k++) 
    arr[k] = 0;
    
    int total_weight=0;
    int total_value=0;
    
    // Start backtracking from max capacity
    int j=capacity;
    
    for(int i=rows-1;i>0;i--){
       
            if(dp[i][j] != dp[i-1][j]){
                arr[i]=1;
                total_weight=total_weight+weight[i];
                total_value=total_value+value[i];
                printf("  Item %d: TAKEN  (weight=%d, value=%d)\n",
                   i, weight[i], value[i]);

                   j=j-weight[i];

            }
        }
        printf("\n");

    printf("  Total weight   : %d / %d\n", total_weight, capacity);
    printf("  Total profit   : %d\n", total_value);
    
    }
    


    



    
