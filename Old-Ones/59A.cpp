#include<iostream>
using namespace std;

// Function Prototype
char* solution(char* input_string);
char capitalize(char c);
char smallize(char c);

#define MAX_SIZE 101

int main(){
    char input_string[MAX_SIZE];
    cin>>input_string;
    cout<<solution(input_string)<<endl;
return 0;
}

char capitalize(char c){
    int offset = 'a'-'A';
    if(c>='a' && c<='z') c=c-offset;
    return c;
}

char smallize(char c){
    int offset = 'a' - 'A';
    if(c>='A' && c<='Z') c=c+offset;
    return c;
}

char* solution(char* input_string){
    int capital_letter_count=0, small_letter_count=0, i=0, str_size=0;
    while(input_string[i]!='\0'){
        if(input_string[i]>='A' && input_string[i]<='Z') capital_letter_count++;
        else if(input_string[i]>='a' && input_string[i]<='z') small_letter_count++;
        i++;
        str_size++;
    }

    if(capital_letter_count<=small_letter_count){
        for(int i=0; i<str_size; i++) input_string[i]=smallize(input_string[i]);
    }
    else if(capital_letter_count>small_letter_count){
        for(int i=0; i<str_size; i++) input_string[i]=capitalize(input_string[i]);
    }
    return input_string;
}
