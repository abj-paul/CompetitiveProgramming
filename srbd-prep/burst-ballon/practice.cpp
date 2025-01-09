#include<iostream>
#include<climits>
#include<vector>
using namespace std;

int give_max_score(const int nBallons, const vector<int>& scores);

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

    cout << give_max_score(nBallons, scores) << endl;
    return 0;
}

int give_max_score(const int nBallons, const vector<int>& scores){
    int n = scores.size();
    vector<vector<int>> dp(n, vector<int>(n,0));

    for(int i=1; i<=nBallons; i++) dp[i][i] = scores[i-1]*scores[i+1];

    for(int length=1; length<nBallons; length++){
        for(int left=1; left<=nBallons-length; left++){
            int right = left + length;
            for(int lastPopped = left; lastPopped<=right; lastPopped++){
                int currScore ;
                if(left==1 && right==nBallons) currScore = scores[lastPopped];
                else currScore = scores[left-1] * scores[right+1];

                int leftScore = lastPopped>left? dp[left][lastPopped-1] : 0;
                int rightScore = lastPopped<right? dp[lastPopped+1][right] : 0;

                dp[left][right] = max(dp[left][right], leftScore + currScore + rightScore);
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cout << dp[i][j] << " ";
        cout << endl;
    }

    return dp[1][nBallons];
}