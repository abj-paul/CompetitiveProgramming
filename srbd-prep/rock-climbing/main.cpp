#include<bits/stdc++.h>
using namespace std;

// Function Prototypes
int find_max_distance(const vector<vector<int>>& grid);

int main(){
    int rows, cols;
    cin>>rows>>cols;
    vector<vector<int>> grid(rows, vector<int>(cols));
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++) cin>>grid[i][j];
    }

    cout << find_max_distance(grid) << endl;

    return 0;
}

bool valid_move(int x, int y, const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();
    if(y < m && y >= 0 && grid[x][y]>0) return true;
    return false;
}

void dfs(int x, int y, const vector<vector<int>>& grid, vector<vector<int>>& dp){
    int n = grid.size(), m = grid[0].size();

    queue<pair<int,int>> q;
    q.push({x,y});

    while(!q.empty()){
        int x = q.front().first, y = q.front().second;
        q.pop();

        //Horizontal movement (left/right) along same level footholdings
        if(valid_move(x, y+1, grid) && dp[x][y] < dp[x][y+1]){
            dp[x][y+1] = dp[x][y]; // moving between rocks at same level poses no difficulty, so same value.
            q.push({x, y+1});
        }
        if(valid_move(x, y-1, grid) && dp[x][y] < dp[x][y-1]){
            dp[x][y-1] = dp[x][y];
            q.push({x, y-1});
        }

        //Vertical movement between any footholdings in the same column
        for(int r=0; r<n; r++){
            if(r != x && grid[r][y]>0){
                int distance = max(abs(r-x), dp[x][y]); //Even though this new climb is only 2 levels, we still needed difficulty level 3 to reach the position where we started this climb
                if(distance < dp[r][y]){
                    dp[r][y] = distance;
                    q.push({r,y});
                }
            }
        }
    }
}

int find_max_distance(const vector<vector<int>>& grid){
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, n-1)); // The dp array stores minimum difficulty needed to reach each position. Starting with initial difficulty of 0 at bottom-left, it propagates through the grid, finding minimum difficulties for all reachable positions.
    dp[n-1][0] = 0; //start
    dfs(n-1, 0, grid, dp);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(3 == grid[i][j]) return dp[i][j]; // grid 3 means goal
        }
    }
    return 0;

}