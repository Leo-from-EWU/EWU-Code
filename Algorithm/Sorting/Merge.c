#include <stdio.h>
#include <stdlib.h>


void my_mergesort(int arr[],int lb,int ub);
void merge(int arr[],int lb,int mid,int ub);

int main(){
    
    int size;
    printf("Enter the size of the Array: ");
    scanf("%d",&size);
    int arr[size];
    printf("Enter the elements of the Array: \n");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }

    my_mergesort(arr,0,size-1);
    
    printf("Merged Array : \n" );
    for (int i = 0; i < size; i++)
    {
        printf("%d\n",arr[i]);
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
