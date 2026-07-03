#include <stdio.h>

int partition(int arr[], int lb, int ub)
{
    int pivot = lb;
    int start = lb + 1;
    int end = ub;
    int temp;

    while (start <= end)
    {
        while (arr[start] <= arr[pivot])
        {
            start++;
        }
        while (arr[end] > arr[pivot])
        {
            end--;
        }

        if (start < end)
        {
            temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
        }
    }
    temp = arr[pivot];
    arr[pivot] = arr[end];
    arr[end] = temp;
    return end;
}


void quicksort(int arr[], int lb, int ub)
{
    if (lb < ub) 
    { 
        int loc = partition(arr, lb, ub); // giving endinfg
        quicksort(arr, lb, loc - 1);
        quicksort(arr, loc + 1, ub);
    }
}
int main()
{

    int size; // for array input size

    printf("Enter the size of the Array: \n");
    scanf("%d", &size);

    int arr[size];
    printf("Enter the elements of the array:\n");

    // input
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    quicksort(arr, 0, size - 1); // sending low=0, and up

    //------ print------

    printf("Quick Sort Array Elements :\n");
    for (int i = 0; i < size; i++)
    {

        printf("%d Element -%d\n", i + 1, arr[i]);
    }

    return 0;
}