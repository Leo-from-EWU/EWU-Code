#include <stdio.h>
#include <stdlib.h>

int main(){
    int arr []= {100,25,10,5,1};
    float s= 5.64*100; // Dollar to Cents
    int len= 5;
    int temp;
    int recount=0;
    

    for(int i=0;i<len;i++){
        temp= arr[i];
        int count=0;
        if(temp<s){
            int j=1;
            
            while(temp * j<s){
                count++;
                j++;
                recount++;
            }
            }
        s= s-(temp*count);
        printf("Coins of %d used %d times,remaining: %2f\n ",temp,count,s);
        
        
    }
    printf("Total Coins Have used:%d",recount);
}