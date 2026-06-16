#include <stdio.h>
struct data{
    int item;
    int weight;
    int benefit;
    int value;
};
struct x{
    int count;
    int result;
};

int main(){
    int total=5;
    int temp;
    int result;
    int profit=0;
    struct x x[]={
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
    };

    // int count[]={0,0,0,0,0};
    struct data arr[]={
        {1,4,12,0},
        {2,8,32,0},
        {3,2,40,0},
        {4,6,30,0},
        {5,1,50,0},
    };
    for(int i=0;i<5;i++){
        arr[i].value= (arr[i].benefit/arr[i].weight);
    }
    // for(int i=0;i<5;i++){
    //     pri-ntf("%d\n: ",arr[i].value);
    // }

    int choto_w=0;
    int boro_w=10;
    int n=44;
    
    while(choto_w<boro_w){
        for(int i=0;i<total;i++){
            if(arr[i].value>arr[i+1].value){
                temp=arr[i].value; //highest value =50
                
            }
        }
        for(int i=0;i<total;i++){
            if(arr[i].value==temp){
                x[i].count= arr[i].item; // item =1;
                x[i].result= choto_w+ arr[i].weight; // 0+1=1;
                boro_w=boro_w-arr[i].weight; //10-1=9
                choto_w= choto_w+arr[i].weight; //1
                arr[i].value=0;
                profit= profit+arr[i].benefit;
                
                 
             }
        }



    }
    profit=profit+ n;
    printf("Total Profit: %d",profit);

    
}
