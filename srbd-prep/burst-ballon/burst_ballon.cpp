#include<iostream>
#include<climits>
#include<vector>

using namespace std;

const int PHI = INT_MIN;

// Function Prototypes
int find_max_score_from_ballon_bursting(int num_ballons, const vector<int>& scores);
int memoization(int l, int r, vector<vector<int>>& dp, const vector<int>& scores);


int main(){
    int num_ballons, input;
    cin>>num_ballons;
    vector<int> scores;
    scores.push_back(1);
    for(int i=0; i<num_ballons; i++){
        cin>>input;
        scores.push_back(input);
    }
    scores.push_back(1);

    cout << find_max_score_from_ballon_bursting(num_ballons, scores) << endl;
    return 0;
}

int find_max_score_from_ballon_bursting(int num_ballons, const vector<int>& scores){
    int n = scores.size();
    vector<vector<int>> dp (n, vector<int>(n, PHI));

    return memoization(1,n-2, dp, scores);
}

int memoization(int l, int r, vector<vector<int>>& dp, const vector<int>& scores){
    if(l>r) return 0;
    if(dp[l][r]!=PHI) return dp[l][r];

    int n = dp.size(), ans = PHI;
    for(int i=l ;i<=r; i++){ //Iterate over all balloons in the range [l,r], treating each i as the last balloon to burst.
        if(l-1==0 && r+1==n-1) ans = max(ans, scores[i] + memoization(l,i-1, dp, scores) + memoization(i+1, r, dp, scores));
        else ans = max(ans, scores[l-1]*scores[r+1] + memoization(l,i-1, dp, scores) + memoization(i+1, r, dp, scores));
    }

    return dp[l][r]=ans;
}

