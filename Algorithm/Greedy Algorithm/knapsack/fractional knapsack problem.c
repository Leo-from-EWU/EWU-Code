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

    struct knapsack arr[] = {
        {1, 4, 12, 0},
        {2, 8, 32, 0},
        {3, 2, 40, 0},
        {4, 6, 30, 0},
        {5, 1, 50, 0},

    };
    for (int i = 0; i < 5; i++)
    {
        arr[i].ratio = (float) arr[i].profit / arr[i].weight;
    }

    int total_weight= 0;
    int fixed_weight=10;



    while(total_weight<fixed_weight){
        int idx=-1;
        int temp=0;
        for(int i=0;i<5;i++){

            if(arr[i].ratio > temp && arr[i].weight!=0){
            temp=arr[i].ratio;
            idx=i;}
        }

        // Fix: was (total_weight < arr[idx].weight) — compared total used vs item weight.
        // Correct check: item fully fits only if (total used + item weight) <= container capacity.
        if(total_weight + arr[idx].weight <= fixed_weight){
            total_weight= total_weight+ arr[idx].weight;
            printf("Item %d , total weight used: %d, Benefit: %d\n",arr[idx].item,arr[idx].weight,arr[idx].profit);
        }
        else{
            // Fractional case: only (fixed_weight - total_weight) units of space remain.
            // Fix: was (1/arr[idx].weight)*profit — integer division always gave 0.
            // Correct: cast to float and use actual remaining space instead of hardcoded 1.
            int remaining = fixed_weight - total_weight;
            float partial_profit = (float)remaining / arr[idx].weight * arr[idx].profit;
            total_weight = fixed_weight; // container is now full, exits the while loop
            printf("Item %d (partial %d/%d units), Partial Benefit: %.2f\n",
                   arr[idx].item, remaining, arr[idx].weight, partial_profit);
        }
        arr[idx].weight=0;



    }


    return 0;
}
