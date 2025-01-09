#include<iostream>
#include<vector>
#include<climits>
#include<queue>

using namespace std;
int find_min_difficulty(const vector<vector<int>>& grid);

int main(){
    int n,m;
    cin>>n>>m;

    vector<vector<int>> grid (n, vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cin>>grid[i][j];
    }

    cout << find_min_difficulty(grid) << endl;
    return 0;
}

bool valid_move(int x, int y,const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();
    if(x>=0 && x<n && y>=0 && y<m && grid[x][y]!=0) return true;
    return false;
}

int find_min_difficulty(const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp (n, vector<int>(m,n-1));

    queue<pair<int,int>> q;
    q.push({n-1,0});
    dp[n-1][0] = 0;

    while(!q.empty()){
        int curr_row = q.front().first, curr_col = q.front().second;
        q.pop();

        // Go left-right
        if(valid_move(curr_row, curr_col-1, grid) && dp[curr_row][curr_col-1]>dp[curr_row][curr_col]){
            dp[curr_row][curr_col-1] = dp[curr_row][curr_col];
            q.push({curr_row, curr_col-1});
        }
        if(valid_move(curr_row, curr_col+1, grid) && dp[curr_row][curr_col+1]>dp[curr_row][curr_col]){
            dp[curr_row][curr_col+1] = dp[curr_row][curr_col];
            q.push({curr_row, curr_col+1});
        }

        // Go up-down
        for(int r=0; r<n; r++){
            if(valid_move(r, curr_col, grid)){
                int difficulty = max(abs(r-curr_row), dp[curr_row][curr_col]);
                if(difficulty < dp[r][curr_col]){
                    dp[r][curr_col] = difficulty;
                    q.push({r,curr_col});
                }
            }
        }
    }

    // Finding solution
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==3) return dp[i][j];
        }
    }
    return -1;
}