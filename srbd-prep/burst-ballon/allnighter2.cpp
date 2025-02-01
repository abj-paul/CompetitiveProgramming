#include<iostream>
#include<vector>
#include<climits>

using namespace std;
int find_max_score(const int nBallons, const vector<int> scores);

int main(){
    int nBallons, input;
    cin>>nBallons;
    vector<int> scores;
    scores.push_back(1);
    for(int i=0; i<nBallons; i++){
        cin>>input;
        scores.push_back(input);
    }
    scores.push_back(1);

    cout << find_max_score(nBallons, scores) << endl;

    return 0;
}

int find_max_score(const int nBallons, const vector<int> scores){
    if(nBallons==1) return scores[nBallons];
    int n = scores.size();
    vector<vector<int>>  dp(n, vector<int>(n, INT_MIN));
    for(int i=1; i<=nBallons; i++) dp[i][i] = scores[i-1]*scores[i+1];

    for(int length=1; length<nBallons; length++){
        for(int left=1; left<nBallons-length+1; left++){
            int right = left + length;
            for(int lastPopped=left; lastPopped<=right; lastPopped++){
                int curr_score;
                if(left==1 && right==nBallons) curr_score = scores[lastPopped];
                else curr_score = scores[left-1]*scores[right+1];

                int leftPartOfBeforeLastPopped = (left<lastPopped)? dp[left][lastPopped-1] : 0;
                int rightPartOfBeforeLastPopped = (right>lastPopped)? dp[lastPopped+1][right] : 0;

                dp[left][right] = max(dp[left][right], leftPartOfBeforeLastPopped+curr_score+rightPartOfBeforeLastPopped);
            }
        }
    }

    return dp[1][nBallons];
}