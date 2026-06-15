#include <stdio.h>
#include <stdlib.h>


void my_mergesort(int arr[],int lb,int ub);
void merge(int arr[],int lb,int mid,int ub);

int main(){
    
    int arr[]= {15,5,24,8,1,3,16,10,20};
    int lb=0;
    int ub=8;

    my_mergesort(arr,lb,ub);

    printf("Sorted array: ");
    for(int i = 0; i <= ub; i++) {
        printf("%d\n", arr[i]);
    }
    

    return 0;
}

void my_mergesort(int arr[],int lb,int ub){
    int mid;

    if(lb<ub){
        mid= (lb+ub)/2;
        my_mergesort(arr,lb,mid);
        my_mergesort(arr,mid+1,ub);
        merge(arr,lb,mid,ub);

    }
}


void merge(int arr[],int lb,int mid,int ub){
    int i=lb;
    int k=lb;
    int j=mid+1;
    int b[ub+1];
    
    while(i<=mid && j<=ub){
        if(arr[i]<arr[j]){
            b[k]=arr[i];
            i++;

        }
        else{
            b[k]= arr[j];
            j++;

        }
        k++;

    }

    if(i > mid){
        while(j<=ub){
            b[k]=arr[j];
            j++;
            k++;

        }
    }
    else{
        while(i<=mid){
            b[k]=arr[i];
            i++;
            k++;
        }
    }

    for(k=lb; k<=ub; k++) {
        arr[k] = b[k];

    }
}
