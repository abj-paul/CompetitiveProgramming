#include<bits/stdc++.h>
using namespace std;

double a,b;
#define epsilon 1e-6
void solution(double A, double B, double C, double D);
int main(){
    int test_cases;
    cin>>test_cases;

    double A,B,C,D;
    while(test_cases--){
        cin>>A>>B>>C>>D;
        solution(A,B,C,D);
        cout<<a<<" "<<b<<endl;
    }

return 0;
}

void solution(double A, double B, double C, double D){
        double arr[4];
        arr[0]=A;
        arr[1]=B;
        arr[2]=C;
        arr[3]=D;

        sort(arr, arr+4);

        double product = arr[3];
        double addition = arr[2];

        double subtraction = sqrt(pow(addition,2)-4*product);
        a = (addition+subtraction)/2;
        b = addition-a;

        double division = a/b;

        bool add_flag=false, sub_flag=false, mul_flag=false, div_flag=false;
        for(int i=0; i<4; i++){
            if(abs(arr[i]-addition)<=epsilon)add_flag=true;
            if(abs(arr[i]-subtraction)<=epsilon) sub_flag=true;
            if(abs(arr[i]-product)<=epsilon) mul_flag=true;
            if(abs(arr[i]-division)<=epsilon) div_flag=true;
        }

        if(add_flag || sub_flag || mul_flag || div_flag){
            a=-1;
            b=-1;
        }
}
