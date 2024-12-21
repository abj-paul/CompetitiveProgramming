#include<bits/stdc++.h>
using namespace std;

const int NCOL = 5;
const int GOLD = 1;
const int ENEMY = 2;
const int EMPTY = 0;
const int BOMB_RANGE = 5;


// Function Prototypes
int find_max_score(const vector<vector<int>>& grid);
int recursively_find_score(int x, int y, int score, int bomb_remaining, const vector<vector<int>>& grid);

int main(){
    int test_cases;
    cin>>test_cases;
    for(int tc=0; tc<test_cases; tc++){
        int nrow;
        cin>>nrow;

        vector<vector<int>> grid(nrow, vector<int>(NCOL));
        for(int i=0; i<nrow; i++){
            for(int j=0; j<NCOL; j++) cin >> grid[i][j];
        }

        cout << "#"<<tc+1<<" "<<find_max_score(grid) << endl;
    }
    return 0;
}


int find_max_score(const vector<vector<int>>& grid){
    int nrow = grid.size();
    return recursively_find_score(nrow, NCOL/2, 0, 1, grid);
}

int recursively_find_score(int x, int y, int score, int bomb_remaining, const vector<vector<int>>& grid){
    if(x-1<0) return score; // reached end
    //cout<<"Level: "<<x<<" Score so far: "<<score<<endl;


    int ans = score;
    if(grid[x-1][y]==GOLD) ans = max(ans, recursively_find_score(x-1, y, score+GOLD, bomb_remaining, grid));
    if(y-1>=0 && grid[x-1][y-1]==GOLD) ans = max(ans, recursively_find_score(x-1, y-1, score+GOLD, bomb_remaining, grid));
    if(y+1<NCOL && grid[x-1][y+1]==GOLD) ans = max(ans, recursively_find_score(x-1, y+1, score+GOLD, bomb_remaining, grid));

    //cout<<"Level "<<x<<" Gold Processed"<<endl;

    // Try going empty cells
    if(grid[x-1][y]==EMPTY) ans = max(ans, recursively_find_score(x-1, y, score+EMPTY, bomb_remaining, grid));
    if(y-1>=0 && grid[x-1][y-1]==EMPTY) ans = max(ans, recursively_find_score(x-1, y-1, score+EMPTY, bomb_remaining, grid));
    if(y+1<NCOL && grid[x-1][y+1]==EMPTY) ans = max(ans, recursively_find_score(x-1, y+1, score+EMPTY, bomb_remaining, grid));

    //cout<<"Level "<<x<<" EMPTY Processed"<<endl;


    // Enemy case
    if(bomb_remaining){
        vector<vector<int>> temp_grid (grid.begin(), grid.end());
        for(int i=x-1; i<=x-BOMB_RANGE; i++){ // killing enemies with bomb
            for(int j=0; j<NCOL; j++){
                if(temp_grid[i][j]==ENEMY) temp_grid[i][j] = EMPTY;
            }
        }
        bomb_remaining--;

        if(grid[x-1][y]==ENEMY) ans = max(ans, recursively_find_score(x-1, y, score+EMPTY, bomb_remaining, temp_grid));
        if(y-1>=0 && grid[x-1][y-1]==ENEMY) ans = max(ans, recursively_find_score(x-1, y-1, score+EMPTY, bomb_remaining, temp_grid));
        if(y+1<NCOL && grid[x-1][y+1]==ENEMY) ans = max(ans, recursively_find_score(x-1, y+1, score+EMPTY, bomb_remaining, temp_grid));
    }else {
        if(grid[x-1][y]==ENEMY) return ans;
        if(y-1>=0 && grid[x-1][y-1]==ENEMY) return ans;
        if(y+1<NCOL && grid[x-1][y+1]==ENEMY) return ans;
    }
    //cout<<"Level "<<x<<" ENEMY Processed"<<endl;

    
    return ans;
}