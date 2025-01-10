#include<bits/stdc++.h>
using namespace std;

const int NCOL = 5, BRANGE = 5;
const int HAS_BOMB_SIGNAL = -1, NOTHING=0, GOLD=1, ENEMY=2;

int find_max_score_in_game(const int nrow, const vector<vector<int>>& grid);

int main(){
    int test_cases;
    cin>>test_cases;
    for(int tc=1; tc<=test_cases; tc++){
        int nrow;
        cin>>nrow;
        vector<vector<int>> grid (nrow, vector<int>(NCOL));
        for(int i=0; i<nrow; i++){
            for(int j=0; j<NCOL; j++) cin>>grid[i][j];
        }
        cout <<"#"<<tc<<" "<< find_max_score_in_game(nrow, grid) << endl;

    }

    return 0;
}

bool valid_position(int row, int col, const vector<vector<int>>& grid){
    int n = grid.size(), m = grid[0].size();
    if(row>=0 && row<n && col>=0 && col<m ) return true;
    return false;
}

int find_max_score_in_game(const int nrow, const vector<vector<int>>& grid){
    int max_score = INT_MIN;
    queue<vector<int>> q;
    q.push({nrow, NCOL/2, 0, HAS_BOMB_SIGNAL});

    while(!q.empty()){
        int row = q.front()[0], col = q.front()[1], score = q.front()[2], bomb_signal = q.front()[3];
        q.pop();

        for(int dy=-1; dy<=1; dy++){
            if(valid_position(row-1, col+dy, grid) && grid[row-1][col+dy]==GOLD){
                max_score = max(max_score, score + GOLD);
                q.push({row-1, col+dy, score+GOLD, bomb_signal});
            }
            else if(valid_position(row-1, col+dy, grid) && grid[row-1][col+dy]==NOTHING){
                max_score = max(max_score, score + NOTHING);
                q.push({row-1, col+dy, score+NOTHING, bomb_signal});
            }
            else if(valid_position(row-1, col+dy, grid) && grid[row-1][col+dy]==ENEMY){
                if(bomb_signal == HAS_BOMB_SIGNAL){
                    max_score = max(max_score, score + NOTHING);
                    q.push({row-1, col+dy, score+NOTHING, row-1});
                }else if(row-1 >= bomb_signal-BRANGE+1){
                    max_score = max(max_score, score + NOTHING);
                    q.push({row-1, col+dy, score+NOTHING, bomb_signal});
                }else {
                    // ENEMY!!
                    max_score = max(max_score, score);
                }
            }
        }
    }

    return max_score;
}