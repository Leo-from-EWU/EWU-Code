#include <stdio.h>
#include <stdlib.h>

int partion(int arr[],int lb,int up);

void quicksort(int arr[],int lb,int up){

    if(lb<up){
        int p= partion(arr,lb,up);
        quicksort(arr,lb,p-1);
        quicksort(arr,p+1,up);
    }
}

int partion(int arr[],int lb,int up){
    int p=lb;
    int lower= lb+1;
    int upper= up;
    int temp;
    while(lower <= upper){
    while(lower <= up && arr[lower] <= arr[p])
    lower++;

    while(upper >= lb && arr[upper] > arr[p])
    upper--;

    if(lower<upper){
         temp= arr[lower];
        arr[lower]= arr[upper];
        arr[upper]=temp;
    }
}
    temp= arr[p];
    arr[p]= arr[upper];
    arr[upper]=temp;
    return upper;

}


int main(){
    int arr[]={7,6,10,5,9,2,1,15,7};

    quicksort(arr,0,8);

    for(int i=0;i<9;i++){
        printf("%d\n",arr[i]);
    }


    return 0;
}