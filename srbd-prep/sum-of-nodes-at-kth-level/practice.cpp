#include<iostream>
#include<string>
using namespace std;

int get_sum_at_kth_level(int K, string& parsed_tree);

int main(){
    int K;
    cin>>K;
    string parsed_tree;
    cin >> parsed_tree;

    cout<< get_sum_at_kth_level(K, parsed_tree) <<endl;

    return 0;
}

int parse_string_to_number(string& number_str){
    int num = 0;
    for(int i=0; i<number_str.size(); i++){
        num = num*10 + (int(number_str[i]-48));
    }
    return num;
}

int get_sum_at_kth_level(int K, string& parsed_tree){
    int level = -1, sum = 0;
    for(int i=0; i<parsed_tree.size(); i++){
        if(parsed_tree[i]=='(') level++;
        else if(parsed_tree[i]==')') level--;
        else if(level==K){
            string number_str = "";
            while(parsed_tree[i]!=')' && parsed_tree[i]!='(' && i<parsed_tree.size()){
                number_str+=parsed_tree[i];
                i++;
            }
            i--;

            sum += parse_string_to_number(number_str);
        }
    }
    return sum;
}