#include<iostream>
#include<climits>
#include<vector>

using namespace std;

const int WHITE=0, GRAY=1, BLACK=2;

const int direction[][4] = { //left,right,up,down
    {0,0,0,0},
    {-1,1,-1,1}, 
    {0,0,-1,1},
    {-1,1,0,0},
    {0,1,-1,0},
    {0,1,0,1},
    {-1,0,0,1},
    {-1,0,-1,0}
};
int newFound = 0;


void dfs(int curr_row, int curr_col, int L, vector<vector<int>>& visited, const vector<vector<int>>& grid);
int find_exploration_count(const int source_row, const int source_col, int L, const vector<vector<int>>& grid);

int main(){
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
        int n,m, source_row, source_col, L;
        cin>>n>>m>>source_row>>source_col>>L;
        vector<vector<int>> grid(n, vector<int>(m));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++) cin>>grid[i][j];
        }

        cout << find_exploration_count(source_row, source_col, L, grid) << endl;
        newFound = 0;
    }
    return 0;
}

int find_exploration_count(const int source_row, const int source_col, int L, const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> visited(n, vector<int>(m, WHITE));

    dfs(source_row, source_col, L, visited, grid);
    return newFound;
}

bool valid_position(int row, int col, const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();
    if(row>=0 && row<n && col>=0 && col<m) return true;
    return false;
}

void dfs(int curr_row, int curr_col, int L, vector<vector<int>>& visited, const vector<vector<int>>& grid){
    //cout << "Traversing coordinate ("<<curr_row<<","<<curr_col<<") with L="<<L<<" and explored="<<newFound<<endl;
    int n = grid.size(), m = grid[0].size();
    if(curr_row<0 || curr_row>=n || curr_col<0 || curr_col>=m) return;
    if(L<=0) return;
    if(visited[curr_row][curr_col]==GRAY) return;

    if(visited[curr_row][curr_col]==WHITE) newFound++;
    visited[curr_row][curr_col] = GRAY;

    int left = direction[grid[curr_row][curr_col]][0];
    int right = direction[grid[curr_row][curr_col]][1];
    int up = direction[grid[curr_row][curr_col]][2];
    int down = direction[grid[curr_row][curr_col]][3];

    //cout<<"Reached here"<<endl;
    
    if(valid_position(curr_row, curr_col+left, grid) && direction[grid[curr_row][curr_col+left]][1]==1) dfs(curr_row, curr_col+left, L-1, visited, grid);

    if(valid_position(curr_row, curr_col+right, grid) && direction[grid[curr_row][curr_col+right]][0]==-1) dfs(curr_row, curr_col+right, L-1, visited, grid);

    if(valid_position(curr_row+up, curr_col, grid) && direction[grid[curr_row+up][curr_col]][3]==1) dfs(curr_row+up, curr_col, L-1, visited, grid);
    
    if(valid_position(curr_row+down, curr_col, grid) && direction[grid[curr_row+down][curr_col]][2]==-1) dfs(curr_row+down, curr_col, L-1, visited, grid);

    visited[curr_row][curr_col] = BLACK;
}