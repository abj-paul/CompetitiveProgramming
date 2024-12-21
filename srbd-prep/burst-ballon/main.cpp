#include<bits/stdc++.h>
using namespace std;

//Function Prototypes
int calculate_max_score(const vector<int>& ballon_values);
int calculate_recursively(const vector<int>& ballon_values, vector<vector<int>>& dp, int start, int end);


int main(){
    int number_of_ballons, input;
    cin>>number_of_ballons;
    vector<int> ballon_values;
    ballon_values.push_back(1);
    for(int i=0; i<number_of_ballons; i++){
        cin>>input;
        ballon_values.push_back(input);
    }
    ballon_values.push_back(1);

    cout << calculate_max_score(ballon_values) << endl;
}

int calculate_max_score(const vector<int>& ballon_values){
    int n = ballon_values.size();
    vector<vector<int>> dp(n, vector<int>(n,-1));

    return calculate_recursively(ballon_values, dp, 1, n-1);
}

int calculate_recursively(const vector<int>& ballon_values, vector<vector<int>>& dp, int start, int end){
    if(start>end) return 0;
    if(dp[start][end]!=-1) return dp[start][end];

    int max_score = INT_MIN, n=ballon_values.size(), score=0;
    for(int i=start; i<=end; i++){
        if(((start-1)==0) && ((end+1)==(n-1))) score = ballon_values[i];
        else score = ballon_values[start-1]*ballon_values[end+1];

        score += calculate_recursively(ballon_values, dp, start, i-1) + calculate_recursively(ballon_values, dp, i+1, end);

        max_score = max(max_score, score);
    }
    return dp[start][end] = max_score;
}
