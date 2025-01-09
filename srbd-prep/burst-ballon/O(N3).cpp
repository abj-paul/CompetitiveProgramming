#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int give_max_score(const int num_of_ballons, const vector<int>& scores) {
    int n = scores.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // Fill DP table
    for (int length = 1; length <= num_of_ballons; length++) {
        for (int left = 1; left <= num_of_ballons - length + 1; left++) {
            int right = left + length - 1;
            for (int last = left; last <= right; last++) {
                int score;
                if (left == 1 && right == num_of_ballons) {
                    score = scores[last];
                } else {
                    score = scores[left - 1] * scores[right + 1];
                }
                
                int before = (last > left) ? dp[left][last - 1] : 0;
                int after = (last < right) ? dp[last + 1][right] : 0;
                
                dp[left][right] = max(dp[left][right],
                                    before + score + after);
            }
        }
    }
    
    return dp[1][num_of_ballons];
}

int main() {
    int num_of_ballons;
    cin >> num_of_ballons;
    
    vector<int> scores;
    scores.push_back(1);  // Add 1 to the beginning
    
    for (int i = 0; i < num_of_ballons; i++) {
        int input;
        cin >> input;
        scores.push_back(input);
    }
    scores.push_back(1);  // Add 1 to the end
    
    cout << give_max_score(num_of_ballons, scores) << endl;
    return 0;
}