#include<iostream>
#include<vector>
#include<climits>

using namespace std;

const int STEP = 1, GOAL = 3, NOTHING = 0;

// Function Prototypes
int find_minimum_difficulty_of_all_path(int n, int m, const vector<vector<int>>& grid);
void recursively_explore_paths(int row, int col, vector<vector<int>>& dp, const vector<vector<int>>& grid);
bool valid_move(int x, int y, const vector<vector<int>>& grid);


int main(){
    int nrows, ncols;
    cin>>nrows>>ncols;

    vector<vector<int>> grid (nrows, vector<int>(ncols));
    for(int i=0; i<nrows; i++){
        for(int j=0; j<ncols; j++) cin>>grid[i][j];
    }

    cout << find_minimum_difficulty_of_all_path(nrows, ncols, grid) << endl;
    return 0;
}

int find_minimum_difficulty_of_all_path(int n, int m, const vector<vector<int>>& grid){
    vector<vector<int>> dp(n, vector<int>(m,n-1));
    dp[n-1][0] = 0;
    recursively_explore_paths(n-1, 0, dp, grid) ;

    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[0].size(); j++){
            if(grid[i][j]==GOAL) return dp[i][j];
        }
    }
    return -1; //error
}

bool valid_move(int x, int y, const vector<vector<int>>& grid){
    if(x>=0 && x<grid.size() && y>=0 && y<grid[0].size() && (grid[x][y]==STEP || grid[x][y]==GOAL)) return true;
    return false;
}

void recursively_explore_paths(int row, int col, vector<vector<int>>& dp, const vector<vector<int>>& grid){
    //cout << "Currently at "<<row<<","<<col<<endl;
    // Left-right
    if(col-1>=0 && valid_move(row, col-1, grid) && dp[row][col-1]>dp[row][col]) {
        dp[row][col-1] = dp[row][col];
        recursively_explore_paths(row, col-1, dp, grid);
    }
    if(col+1<grid[0].size() && valid_move(row, col+1, grid) && dp[row][col+1]>dp[row][col]){ 
        dp[row][col+1] = dp[row][col];
        recursively_explore_paths(row, col+1, dp, grid);
    }

    // Up-down 
    for(int r=0; r<grid.size(); r++){
        if(valid_move(r,col,grid)){
            int difficulty = max(abs(r-row), dp[row][col]);
            if(dp[r][col]>difficulty) {
                dp[r][col] = difficulty;
                recursively_explore_paths(r,col,dp,grid);
            }
        }
    }
}