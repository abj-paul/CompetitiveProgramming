#include<bits/stdc++.h>
using namespace std;

// Function Prototypes
int sum_at_kth_level(int k, string tree_str);
int parse_string_to_number(string number_str);


int main(){
    int k;
    cin >> k;
    string tree_str;
    cin >> tree_str ;

    cout << sum_at_kth_level(k, tree_str) << endl;

    return 0;
}

int sum_at_kth_level(int k, string tree_str){
    int sum = 0, current_level = -1;

    for(int i=0; i<tree_str.size(); i++){
        if(tree_str[i]=='(') current_level++;
        else if(tree_str[i]==')') current_level--;
        else if(current_level == k) {
            string number_str = "";
            while(i<tree_str.size() && tree_str[i] != '(' && tree_str[i]!=')'){
                number_str += tree_str[i];
                i++;
            }
            sum += parse_string_to_number(number_str);
            i--;
        }
    }
    
    return sum;
}

int parse_string_to_number(string number_str){
    int number = 0;
    for(int i=0; i<number_str.size(); i++){
        number = number*10 + (int(number_str[i]-48));
    }
    return number;
}