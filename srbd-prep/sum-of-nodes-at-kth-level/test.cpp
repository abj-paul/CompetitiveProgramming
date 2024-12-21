#include<bits/stdc++.h>
using namespace std;

int to_number(string str){
    int num = 0;
    for(int i=0; i<str.size(); i++){
        num = num*10+(int(str[i])-48);
    }
    return num;
}

int main(){
    int k;
    cin >> k;
    string s; 
    cin >> s;

    int level = -1, sum = 0;
    for(int i=0; i<s.size(); i++){
        if(s[i] == '(')  level++;
        else if(s[i]==')') level --;
        else if(level==k){
            string tmp;
            while(i<s.size() && s[i] != '(' && s[i] != ')'){
                tmp.push_back(s[i]);
                i++;
            }
            i--;
            sum += to_number(tmp);
        }
    }
    cout << sum << endl;
}