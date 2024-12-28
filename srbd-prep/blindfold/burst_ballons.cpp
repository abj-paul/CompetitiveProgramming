#include<iostream>
#include<vector>
#include<climits>

using namespace std;

int main(){
    int num_of_ballons, input;
    cin>>num_of_ballons;

    vector<int> ballon_scores;
    ballon_scores.push_back(1);
    for(int i=0; i<num_of_ballons; i++){
        cin>>input;
        ballon_scores.push_back(input);
    }
    ballon_scores.push_back(1);

    cout << find_max_score(num_of_ballons, ballon_scores) << endl;

    return 0;
}

int find_max_score(int num_of_ballons, const vector<int>& ballon_scores){
    int n = ballon_scores.size();
    vector<vector<int>> dp (n, vector<int>(n));

    return recursively_find_score(1, num_of_ballons, dp, ballon_scores);
}

int recursively_find_score(int start, int end, vector<vector<int>>& dp, const vector<int>& ballon_scores){

    int max_score = INT_MIN;
    for(int i=start; i<=end; i++){
        if(i-1==0 && i+1==)
    }

}