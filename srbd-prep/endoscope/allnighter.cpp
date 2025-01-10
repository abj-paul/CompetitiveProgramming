#include<iostream>
#include<vector>
#include<climits>
using namespace std;

const int directions[][4] = { //left,right,up,down
    {0,0,0,0},
    {-1,1,-1,1}, // all direction pipe
    {0,0,-1,1},
    {-1,1,0,0},
    {0,1,-1,0},
    {0,1,0,1},
    {-1,0,0,1},
    {-1,0,-1,0}
};

int newFound = 0;
const int WHITE=0, GRAY=1, BLACK=2;

void dfs(int row, int col, int L, vector<vector<int>>& visited, const vector<vector<int>>& grid);
void explore(int start_row, int start_col, int L, const vector<vector<int>>& grid);

int main(){
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
        int n,m,start_row,start_col,L;
        cin>>n>>m>>start_row>>start_col>>L;

        vector<vector<int>> grid (n, vector<int>(m));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++) cin>>grid[i][j];
        }

        explore(start_row, start_col, L, grid);

        cout<<newFound<<endl;
        newFound = 0;
    }

    return 0;
}

void explore(int start_row, int start_col, int L, const vector<vector<int>>& grid){
    int n=grid.size(), m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, WHITE));

    dfs(start_row, start_col, L, visited, grid);
}


bool valid_position(int row, int col, const vector<vector<int>>& grid){
    int n=grid.size(), m = grid[0].size();
    if(row>=0 && row<n && col>=0 && col<m) return true;
    return false;
}

void dfs(int row, int col, int L, vector<vector<int>>& visited, const vector<vector<int>>& grid){
    int n=grid.size(), m = grid[0].size();
    if(L<=0) return;
    if(row<0 || row>=n || col<0 || col>=m) return;
    if(visited[row][col]==GRAY) return;
    
    if(visited[row][col]==WHITE){
        newFound++;
        visited[row][col] = GRAY;
    }

    // left right
    int left = directions[grid[row][col]][0];
    int right = directions[grid[row][col]][1];
    int up = directions[grid[row][col]][2];
    int down = directions[grid[row][col]][3];

    if(valid_position(row, col+left, grid) && directions[grid[row][col+left]][1]==1) dfs(row, col+left, L-1, visited, grid);
    if(valid_position(row, col+right, grid) && directions[grid[row][col+right]][0]==-1) dfs(row, col+right, L-1, visited, grid);
    if(valid_position(row+up, col, grid) && directions[grid[row+up][col]][3]==1) dfs(row+up, col, L-1, visited, grid);
    if(valid_position(row+down, col, grid) && directions[grid[row+down][col]][2]==-1) dfs(row+down, col, L-1, visited, grid);

    visited[row][col] = BLACK;
}