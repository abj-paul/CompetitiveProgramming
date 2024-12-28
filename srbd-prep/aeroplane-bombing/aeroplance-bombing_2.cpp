#include<iostream>
#include<climits>
#include<vector>
#include<queue>

using namespace std;

const int MAX_WIDTH=5, ENEMY=2, GOLD=1, NOTHING=0, BOMB_RANGE=5, HAS_BOMB_SIGNAL=-1;

// Function Prototypes 
int find_max_score_using_bfs(int n, const vector<vector<int>>& grid);
int find_max_score_in_game(int n, const vector<vector<int>>& grid);

int main(){
    int test_cases;
    cin>>test_cases;
    for(int tc=1; tc<=test_cases; tc++){
        int n;
        cin>>n;

        vector<vector<int>> grid (n, vector<int>(MAX_WIDTH));
        for(int i=0; i<n; i++){
            for(int j=0; j<MAX_WIDTH; j++){
                cin>>grid[i][j];
            }
        }

        cout<<tc<<"# "<<find_max_score_in_game(n,grid)<<endl;
    }
    return 0;
}

int find_max_score_in_game(int n, const vector<vector<int>>& grid){

    return find_max_score_using_bfs(n,grid);
}

int find_max_score_using_bfs(int n, const vector<vector<int>>& grid){
    queue<vector<int>> q;
    q.push({n,MAX_WIDTH/2,0,HAS_BOMB_SIGNAL});

    int max_score = INT_MIN;

    while(!q.empty()){
        int row = q.front()[0], col = q.front()[1], score_so_far = q.front()[2], bomb_status = q.front()[3];
        q.pop();
        for(int dy=-1; dy<=1; dy++){
            if(row-1<0 || col+dy <0 || col+dy>=MAX_WIDTH) continue;

            if(grid[row-1][col+dy]!=ENEMY) {
                q.push({row-1, col+dy, score_so_far+grid[row-1][col+dy], bomb_status});
                max_score = max(max_score, score_so_far+grid[row-1][col+dy]);
            }
            else {
                if(bomb_status==HAS_BOMB_SIGNAL){
                    q.push({row-1, col+dy, score_so_far+0, row}); // bomb em
                    max_score = max(max_score, score_so_far+0);
                }else {
                    int bomb_start_loc = bomb_status;
                    if(bomb_start_loc-BOMB_RANGE>=row-1){
                        q.push({row-1, col+dy, score_so_far+0, row});
                    }
                    else {
                        max_score = max(max_score, score_so_far); //game ends
                    }
                }
            }
        }
    }

    return max_score;
}