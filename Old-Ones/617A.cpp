#include<iostream>
using namespace std;
int solution(int x);

int main(){
    int x;
    cin>>x;
    cout<<solution(x)<<endl;


return 0;
}

int solution(int x){
    int steps=0;
    steps = steps + x/5;
    x = x%5;
    steps = steps + x/4;
    x = x%4;
    steps = steps + x/3;
    x = x%3;
    steps = steps + x/2;
    x = x%2;
    steps = steps + x/1;
    x = x%1;
    return steps;
}
