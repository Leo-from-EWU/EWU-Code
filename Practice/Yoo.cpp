#include <iostream>
using namespace std;

int main(){
    int x;
    int y;
    cout<<"Enter the number for x\n";
    cin>>x;
    cout<<"Enter the number for y\n";
    cin>>y;
    char z;
    cout<<"Enter the operators:\n";
    cin>>z;
    int s;


    switch (z)
    {
    case '+':
        s=x+y;
        cout<<"YOur number is:"<<s;
    
    default:
        break;
    }

}