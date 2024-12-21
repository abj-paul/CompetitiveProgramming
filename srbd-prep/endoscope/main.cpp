#include<bits/stdc++.h>
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

const int NO_DIRECTION = 0;

// Function Prototype
int find_endoscope_max_depth(int m, int n, int r, int c, int l, const vector<vector<int>>& grid);
void dfs(int i, int j, int l, int& explored_pipe_count, const vector<vector<int>>& grid, vector<vector<int>>& visited,vector<vector<int>>& dfsvisited);

int main(){
    int num_of_test_cases;
    cin>>num_of_test_cases;

    for(int tc=0; tc<num_of_test_cases; tc++){
        int n,m,r,c,l;
        cin>>n>>m>>r>>c>>l;
        vector<vector<int>> grid (m, vector<int>(m));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cin >> grid[i][j];
            }
        }

        cout<< find_endoscope_max_depth(m,n,r,c,l, grid)<<endl;
    }
    return 0;
}

int find_endoscope_max_depth(int m, int n, int r, int c, int l, const vector<vector<int>>& grid){
    vector<vector<int>> visited(n, vector<int>(m,0)), dfsvisited(n, vector<int>(m,0));
    int explored_pipe_count = 0;
    dfs(r,c,l,explored_pipe_count,grid,visited,dfsvisited);
    return explored_pipe_count;
}

void dfs(int i, int j, int l, int& explored_pipe_count, const vector<vector<int>>& grid, vector<vector<int>>& visited,vector<vector<int>>& dfsvisited){
    int n = grid.size();
    int m = grid[0].size();
    if(i<0 || i>=n || j<0 || j>=m) return;

    if(grid[i][j]==NO_DIRECTION) return;
    if(dfsvisited[i][j]) return;
    if(l<=0) return; // what this?
    if(!visited[i][j])  {
        explored_pipe_count++;
        visited[i][j] = 1;
    }
    
    dfsvisited[i][j] = 1;

    int left = directions[grid[i][j]][0];
    int right = directions[grid[i][j]][1];
    int up = directions[grid[i][j]][2];
    int down = directions[grid[i][j]][3];

    if(j+left>=0 && j+left<m && directions[grid[i][j+left]][1]==1) dfs (i,j+left,l-1, explored_pipe_count, grid, visited, dfsvisited);
    if(j+right>=0 && j+right<m && directions[grid[i][j+right]][0]==-1) dfs (i,j+right,l-1, explored_pipe_count, grid, visited, dfsvisited);
    if(i+up>=0 && i+up<n && directions[grid[i+up][j]][3]==1) dfs (i+up,j,l-1, explored_pipe_count, grid, visited, dfsvisited);
    if(i+down>=0 && i+down<n && directions[grid[i+down][j]][2]==-1) dfs (i+down,j,l-1, explored_pipe_count, grid, visited, dfsvisited);

    dfsvisited[i][j]=0;
}