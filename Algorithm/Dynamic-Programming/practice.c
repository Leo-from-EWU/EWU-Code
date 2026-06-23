#include <stdio.h>
#include <stdlib.h>

struct knapsack
{
    int item;
    int weight;
    int profit;
    float ratio;
};

int main()
{
    int total_weight = 10;
    int small_weight = 0; // how much weight is filling
    int remaining_weight;

    // traker
    int item_tracker;
    int weight_tracker;
    int profit_tracker;



    struct knapsack arr[] = {
        {1, 4, 12, 0},
        {2, 8, 32, 0},
        {3, 2, 40, 0},
        {4, 6, 30, 0},
        {5, 1, 50, 0},

    };
    for(int i=0;i<5;i++){
        arr[i].ratio= arr[i].profit / arr[i].weight;

    }
    
    while(small_weight<total_weight){

    int index=-1;
    float higest_ratio=0;


    for(int i=0;i<5;i++){
        if(arr[i].ratio!=0){
        if(arr[i].ratio > higest_ratio){
            
            //store the all item, weight,profit, ratio

            item_tracker= arr[i].item;
            weight_tracker= arr[i].weight;
            profit_tracker=arr[i].profit;
            higest_ratio= arr[i].ratio;
            index=i; // storing the index to rmv the array.


        }
    }

    }
    if(index==-1)
    break;

    remaining_weight= total_weight-small_weight; // find the remaining weight
    
    
    if(weight_tracker <= remaining_weight){
        small_weight = small_weight+ weight_tracker;

    }


}
}