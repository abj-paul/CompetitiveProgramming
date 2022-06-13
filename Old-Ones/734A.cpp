#include<iostream>
using namespace std;
string solution(string input_str);

int main(){
    int s;
    cin>>s;
    string input_str;
    cin>>input_str;
    cout<<solution(input_str);
return 0;
}

string solution(string input_str){
    int anton=0, danik=0;
    for(int i=0; i<input_str.size(); i++){
        if(input_str[i]=='A') anton++;
        else if(input_str[i]=='D') danik++;
    }

    if(anton>danik) return "Anton";
    else if(anton<danik) return "Danik";
    else return "Friendship";
}
