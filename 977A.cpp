#include<iostream>
using namespace std;

#define MAX_SIZE 100
char* solution(char* number, int k);

int main(){
    int k;
    char number[MAX_SIZE];
    cin>>number>>k;
    cout<<solution(number,k)<<endl;
return 0;
}

char* solution(char* number, int k){
    int last_digit_index=0;
    while(number[last_digit_index]!='\0') last_digit_index++;
    last_digit_index--;

    while(k--){
        if(number[last_digit_index]>='1' && number[last_digit_index]<='9') number[last_digit_index]=number[last_digit_index]-1;
        else if(number[last_digit_index]=='0') last_digit_index--;
    }

    // Constructing output string
    char* output_string = (char*)calloc(last_digit_index+1, sizeof(char));
    for(int i=0; i<=last_digit_index; i++) output_string[i]=number[i];
    output_string[last_digit_index+1]='\0';

    return output_string;
}

