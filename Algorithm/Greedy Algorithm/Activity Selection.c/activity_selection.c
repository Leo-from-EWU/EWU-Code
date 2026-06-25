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

  int start[] = {1,3,0,5,3,5,6,8,8,2,12};
  int finish[] = {4,5,6,7,8,9,10,11,12,13,14};

  int n = sizeof(start) / sizeof(start[0]);
  printf("The 1 activity will start from: %d, and end at %d\n",start[0],finish[0]);
  // %d\n",start[0],finish[0]);
  activity_selector(start, finish, n);
  return 0;
}