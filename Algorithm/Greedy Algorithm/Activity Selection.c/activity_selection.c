#include <stdio.h>

void activity(int start[], int finish[], int n)
{
    int temp = 0;
    int tt;
    int count = 0;

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(finish[j]>finish[j+1]){
                tt= finish[j];
                finish[j]=finish[j+1];
                finish[j+1]=tt;

                tt=start[j];
                start[j]=start[j+1];
                start[j+1]=tt;
            }
        }
    }
    printf("The activity will start from %d to %d\n", start[0], finish[0]);

    for (int i = 0; i < n; i++)
    {
        if (start[i] >= finish[temp])
        {
            temp = i;
            count++;

            printf("The activity will start from %d to %d\n ", start[i], finish[i]);
        }
    }
    printf("%d : Max", count+1);
}
int main()
{
    int n;
    printf("Enter the activity number: \n");
    scanf("%d", &n);

    int start[n];
    int finish[n];

    printf("Enter the activities starting & ending: (s,f) \n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &start[i], &finish[i]);
    }

    
    activity(start, finish, n);
}