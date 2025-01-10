#include<iostream>
#include<vector>
#include<climits>
#include<queue>
using namespace std;

int max_difficulty_in_rock_climbing(const vector<vector<int>>& grid);

int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<int>> grid (n, vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cin>>grid[i][j];
    }

    cout << max_difficulty_in_rock_climbing(grid) << endl;

    return 0;
}

int valid_move(int row, int col, const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();
    if(row >=0 && row<n && col>=0 && col<m && grid[row][col]!=0) return true;
    return false; 
}

int max_difficulty_in_rock_climbing(const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();

    vector<vector<int>> dp (n, vector<int>(m, n-1));
    queue<pair<int,int>> q;
    q.push({n-1,0});
    dp[n-1][0] = 0;

    while(!q.empty()){
        int row = q.front().first, col = q.front().second;
        q.pop();
        
        // left right
        if(valid_move(row, col-1, grid) && dp[row][col-1]>dp[row][col]){
            dp[row][col-1] = dp[row][col];
            q.push({row, col-1});
        }
        if(valid_move(row, col+1, grid) && dp[row][col+1]>dp[row][col]){
            dp[row][col+1] = dp[row][col];
            q.push({row, col+1});
        }

        // up down
        for(int i=0; i<n; i++){
            if(valid_move(i,col,grid)){
                int difficulty = max(abs(row-i), dp[row][col]);
                if(difficulty < dp[i][col]){
                    dp[i][col] = difficulty;
                    q.push({i,col});
                }
            }
        }
    }

    // Finding Answer
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            if(grid[i][j]==3) return dp[i][j];
    }
    return -1;
}