#include<iostream>
#include<string>

using namespace std;

// Function Prototypes
int sum_at_kth_level(int k, const string& parsed_tree);

int main(){
    int K;
    cin>>K;
    string parsed_tree;
    cin>>parsed_tree;

    cout << sum_at_kth_level(K, parsed_tree) <<endl;
    
    return 0;
}

int parse_number_from_string(string num_str){
    int number = 0;

    for(int i=0; i<num_str.size(); i++){
        number = number*10 + (char(num_str[i])-48);
    }

    return number;
}

int sum_at_kth_level(int k, const string& parsed_tree){
    int curr_level = -1, sum=0;
    for(int i=0; i<parsed_tree.size(); i++){
        if(parsed_tree[i]=='(') curr_level++;
        else if(parsed_tree[i]==')') curr_level--;
        else if(curr_level==k){
            string number = "";
            while(parsed_tree[i]!='(' && parsed_tree[i]!=')' && i<parsed_tree.size()){
                number+=parsed_tree[i];
                i++;
            }
            //cout << parsed_tree[i] << " is at level " << curr_level <<endl;
            int curr_sum = parse_number_from_string(number);
            sum+=curr_sum;
            if(curr_sum!=0) i--;
            //cout << number << " was converted to sum "<<sum <<endl;
        }
    }

    return sum;
}