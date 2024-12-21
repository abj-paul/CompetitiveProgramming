#include<bits/stdc++.h>
using namespace std;

const int GOAL = 3;
const int STEP = 1;
const int EMPTY = 0;

// Function Prototype
int find_least_difficulty_in_rock_climbing(const vector<vector<int>>& grid);

int main(){
    int n,m;
    cin>>n>>m;
    
    vector<vector<int>> grid(n, vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cin>>grid[i][j];
    }

    cout << find_least_difficulty_in_rock_climbing(grid) << endl;

    return 0;
}

bool valid_move(int x, int y,const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();

    if(y>=0 && y<m && grid[x][y]!=0){ // x>=0 && x<n && 
        return true;
    }
    return false;
}

void dfs(int x, int y, const vector<vector<int>>& grid, vector<vector<int>>& dp){
    int n = grid.size(), m = grid[0].size();
    queue<pair<int,int>> q;
    q.push({x,y});

    while(!q.empty()){
        //cout << "Trying "<<x<<","<<y<<"="<<dp[x][y]<<endl;
        x = q.front().first, y = q.front().second;
        q.pop();

        // Move left right
        if(valid_move(x, y-1, grid) && dp[x][y-1]>dp[x][y]){
            dp[x][y-1] = dp[x][y];
            q.push({x, y-1});
        }
        if(valid_move(x, y+1, grid) && dp[x][y+1]>dp[x][y]){
            dp[x][y+1] = dp[x][y];
            q.push({x, y+1});
        }
        // Move up down
        int distance = 0;
        for(int r=0; r<n; r++){
            if(grid[r][y]==STEP || grid[r][y]==GOAL){
                distance = max(abs(r-x), dp[x][y]);
                if(distance < dp[r][y]){
                    dp[r][y] = distance;
                    q.push({r,y});
                }
            }
        }
    }

}

int find_least_difficulty_in_rock_climbing(const vector<vector<int>>& grid){
    int n = grid.size(), m=grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, n-1));
    dp[n-1][0] = 0;

    dfs(n-1, 0, grid, dp);

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==GOAL) return dp[i][j];
        }
    }
    return 0;
}