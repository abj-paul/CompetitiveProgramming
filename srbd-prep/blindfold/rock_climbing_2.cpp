#include<iostream>
#include<climits>
#include<vector>
#include<queue>

using namespace std;

const int GOAL=3, STEP=1, NOTHING=0;

// Function Prototypes
void bfs_traversal(vector<vector<int>>& dp, const vector<vector<int>>& grid);
int find_path_with_min_difficulty(int nrow, int ncol, const vector<vector<int>>& grid);
int valid_move(int x, int y, const vector<vector<int>>& grid);

int main(){
    int nrow, ncol;
    cin>>nrow>>ncol;

    vector<vector<int>> grid(nrow, vector<int>(ncol));
    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncol; j++) cin>>grid[i][j];
    }

    cout << find_path_with_min_difficulty(nrow, ncol, grid) <<endl;

    return 0;
}

int find_path_with_min_difficulty(int nrow, int ncol, const vector<vector<int>>& grid){
    vector<vector<int>> dp(nrow, vector<int>(ncol, nrow-1)); //dp[i][j] represents the minimum difficulty required to reach the cell (i, j)
    bfs_traversal(dp, grid);

    for(int i=0; i<nrow; i++)
        for(int j=0; j<ncol; j++)
            if(grid[i][j]==GOAL) return dp[i][j];
    return -1; //error
}   

int valid_move(int x, int y, const vector<vector<int>>& grid){
    int n=grid.size(), m = grid[0].size();

    if(x>=0 && x<n && y>=0 && y<m && (grid[x][y]==STEP || grid[x][y]==GOAL)) return true;
    return false;
}

void bfs_traversal(vector<vector<int>>& dp, const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();

    queue<pair<int,int>> q;
    q.push({n-1,0}); // staring position
    dp[n-1][0] = 0;

    
    while(!q.empty()){
        pair<int,int> curr_pos = q.front();
        int row = curr_pos.first, col = curr_pos.second;
        q.pop();

        // Left, Right
        if(valid_move(row, col-1, grid) && dp[row][col]<dp[row][col-1]) { // This effectively "prunes" paths that do not offer an improvement, ensuring that the BFS/DFS focuses only on paths that could potentially lead to a lower difficulty.
            dp[row][col-1] = dp[row][col];
            q.push({row, col-1});
        }
        if(valid_move(row, col+1, grid) && dp[row][col]<dp[row][col+1]) {
            dp[row][col+1] = dp[row][col];
            q.push({row, col+1});
        }

        // up down
        for(int r=0; r<n; r++){
            if(valid_move(r,col,grid)){
                int difficulty = max(abs(r-row), dp[row][col]); // one time movement difficulty
                if(difficulty<dp[r][col]){
                    dp[r][col] = difficulty;
                    q.push({r,col});
                }
            }
        }
    }
}

