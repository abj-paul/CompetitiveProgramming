#include<iostream>
using namespace std;
int* extract_digit(int year);
int solution(int year);

int main(){
    int year;
    cin>>year;
    cout<<solution(year);
return 0;
}

int solution(int year){
    year++;
    while(1){
        int* digits = extract_digit(year);
        bool exists[10];
        for(int i=0; i<10; i++) exists[i]=false; //initialize
        for(int i=0; i<4; i++){
            if(exists[digits[i]]){
                free(digits);
                year++;
                continue;
             }
            exists[digits[i]]=true;
        }
        return year;
    }
}

int* extract_digit(int year){
    int* digits = (int*)calloc(10, sizeof(int));
    int index=0;
    while(year){
        digits[index] = year%10;
        year/=10;
        index++;
    }
    return digits;
}
