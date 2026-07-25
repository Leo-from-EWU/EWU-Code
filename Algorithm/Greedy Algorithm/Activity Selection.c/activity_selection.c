#include <stdio.h>
#include <stdlib.h>

void activity_selector(int start[], int finish[], int n) {
int temp=0;
int count=1;

for(int i=0;i<n;i++){
    if(start[i]>= finish[temp]){
        count++;
        temp=i;
        printf("The %d activity will start from %d, and end at %d\n",count,start[i],finish[temp]);
    }
}
printf("Max: %d",count);
}
int main() {

  int start[] = {10,12,20};
  int finish[] = {20,25,30};

  int n = sizeof(start) / sizeof(start[0]);
  printf("The 1 activity will start from: %d, and end at %d\n",start[0],finish[0]);
  // %d\n",start[0],finish[0]);
  activity_selector(start, finish, n);
  return 0;
}