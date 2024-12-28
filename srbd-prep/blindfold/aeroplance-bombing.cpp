#include<iostream>
#include<vector>
#include<climits>

using namespace std;

const int NOTHING=0, GOLD=1, ENEMY=2;
const int MAX_WIDTH = 5;
const int BOMB_RANGE = 5;

// Function Prototypes
int find_max_score_in_game(int n, const vector<vector<int>>& grid);
void throw_bomb(int curr_location, vector<vector<int>>& new_grid);
int recursively_find_score(int row, int col, int score_so_far, int bombCount, const vector<vector<int>>& grid);


int main(){
    int test_cases;
    cin>>test_cases;
    for(int tc=1; tc<=test_cases; tc++){
        int n;
        cin>>n;
        vector<vector<int>> grid(n, vector<int>(MAX_WIDTH));
        for(int i=0; i<n; i++){
            for(int j=0; j<MAX_WIDTH; j++) cin>>grid[i][j];
        }
        cout << tc <<"# "<< find_max_score_in_game(n, grid) <<endl;
    }

}

int find_max_score_in_game(int n, const vector<vector<int>>& grid){

    return recursively_find_score(n,MAX_WIDTH/2,0,1,grid);
}

void throw_bomb(int curr_location, vector<vector<int>>& new_grid){
    //cout << "Throwing bomb at location "<<curr_location<<endl;
    for(int i=curr_location-1; i>=curr_location-BOMB_RANGE; i--){
        for(int j=0; j<MAX_WIDTH; j++){
            if(i>=0 && j>=0 && new_grid[i][j]==ENEMY) new_grid[i][j] = NOTHING;
        }
    }
}


int recursively_find_score(int row, int col, int score_so_far, int bombCount, const vector<vector<int>>& grid){
    //cout << "Recursively exploring ("<<row<<","<<col<<") with current score "<<score_so_far<<" and bomb "<<bombCount<<endl;
    int n = grid.size();
    if(row<=0 || col<=0 || col>=MAX_WIDTH) return score_so_far;
    
    int ans = score_so_far;
    // Explore Gold Choices
    if(grid[row-1][col]==GOLD) ans = max(ans, recursively_find_score(row-1, col, score_so_far+GOLD, bombCount, grid));
    if(grid[row-1][col-1]==GOLD) ans = max(ans, recursively_find_score(row-1, col-1, score_so_far+GOLD, bombCount, grid));
    if(grid[row-1][col+1]==GOLD) ans = max(ans, recursively_find_score(row-1, col+1, score_so_far+GOLD, bombCount, grid));

    // Explore Nothing Choices
    if(grid[row-1][col]==NOTHING) ans = max(ans, recursively_find_score(row-1, col, score_so_far+NOTHING, bombCount, grid));
    if(grid[row-1][col-1]==NOTHING) ans = max(ans, recursively_find_score(row-1, col-1, score_so_far+NOTHING, bombCount, grid));
    if(grid[row-1][col+1]==NOTHING) ans = max(ans, recursively_find_score(row-1, col+1, score_so_far+NOTHING, bombCount, grid));

    if(bombCount==1){
        // Explore Enemy Choices with bomb
        vector<vector<int>> temp_grid(grid.begin(), grid.end());
        throw_bomb(row, temp_grid);
        bombCount--;

        // Explore Gold Choices
        if(temp_grid[row-1][col]==GOLD) ans = max(ans, recursively_find_score(row-1, col, score_so_far+GOLD, bombCount, temp_grid));
        if(temp_grid[row-1][col-1]==GOLD) ans = max(ans, recursively_find_score(row-1, col-1, score_so_far+GOLD, bombCount, temp_grid));
        if(temp_grid[row-1][col+1]==GOLD) ans = max(ans, recursively_find_score(row-1, col+1, score_so_far+GOLD, bombCount, temp_grid));

        // Explore Nothing Choices
        if(temp_grid[row-1][col]==NOTHING) ans = max(ans, recursively_find_score(row-1, col, score_so_far+NOTHING, bombCount, temp_grid));
        if(temp_grid[row-1][col-1]==NOTHING) ans = max(ans, recursively_find_score(row-1, col-1, score_so_far+NOTHING, bombCount, temp_grid));
        if(temp_grid[row-1][col+1]==NOTHING) ans = max(ans, recursively_find_score(row-1, col+1, score_so_far+NOTHING, bombCount, temp_grid));
    }

    // Explore Enemy Choices
    // if(grid[row-1][col]==ENEMY) return score_so_far;
    // if(grid[row-1][col-1]==ENEMY) return score_so_far;
    // if(grid[row-1][col+1]==ENEMY) return score_so_far;
    return ans;
}