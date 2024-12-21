#include<bits/stdc++.h>
using namespace std;

// Function Prototypes
int calculate_max_score(const vector<int>& ballon_values, int num_of_ballons);
int recursively_calculate_score(const vector<int>& ballon_values, int start, int end);

int main(){
    int num_of_ballons, input;
    cin>>num_of_ballons;
    vector<int> ballon_values;
    ballon_values.push_back(1);
    for(int i=0; i<num_of_ballons; i++){
        cin>>input;
        ballon_values.push_back(input);
    }
    ballon_values.push_back(1);

    cout << calculate_max_score(ballon_values, num_of_ballons) << endl;
}

int calculate_max_score(const vector<int>& ballon_values, int n){
    return recursively_calculate_score(ballon_values, 1, n);
}

int recursively_calculate_score(const vector<int>& ballon_values, int start, int end){
    if(start>end) return 0;
    
    int max_score = INT_MIN, score=0;
    for(int i=start; i<=end; i++){
        if ((start-1)==0 && (end+1)==(ballon_values.size()-1)) score = ballon_values[i]; // Root case
        else score = ballon_values[start-1]*ballon_values[end+1];
        
        score += recursively_calculate_score(ballon_values, start, i-1) + recursively_calculate_score(ballon_values, i+1, end);
        max_score = max(max_score, score);
    }
    //cout << "Range: " << start <<"-"<<end<<"="<<max_score<<endl;

    return max_score;
}