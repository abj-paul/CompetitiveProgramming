#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

const int NCOL = 5, GOLD=1, ENEMY=2, NOTHING=0, HAS_BOMB_SIGNAL=-1, BRANGE = 5;
int find_max_score_from_game(const int n, const vector<vector<int>>& grid);

int main(){
    int test_cases;
    cin>>test_cases;
    for(int tc=1; tc<=test_cases; tc++) {
        int nrow;
        cin>>nrow;
        vector<vector<int>> grid(nrow, vector<int>(NCOL));
        for(int i=0; i<nrow; i++){
            for(int j=0; j<NCOL; j++) cin>>grid[i][j];
        }

        cout <<"#"<<tc<<" "<<find_max_score_from_game(nrow, grid) << endl;
    }
    return 0;
}

int find_max_score_from_game(const int n, const vector<vector<int>>& grid){
    int final_score = INT_MIN;
    queue<vector<int>> q;
    q.push({n,NCOL/2, 0 ,HAS_BOMB_SIGNAL});

    while(!q.empty()){
        int posx = q.front()[0], posy = q.front()[1], score = q.front()[2], bombSignal = q.front()[3];
        q.pop();
        
        final_score = max(final_score, score);
        
        //cout <<"Exploring bfs at position ("<<posx<<","<<posy<<") with score of "<<score<<endl;


        for(int dx=-1; dx<=1; dx++){
            if(posy+dx<0 || posy+dx>=NCOL || posx-1<0) continue;
            if(grid[posx-1][posy+dx]==GOLD) q.push({posx-1, posy+dx, score + GOLD, bombSignal});
            else if(grid[posx-1][posy+dx]==NOTHING) q.push({posx-1, posy+dx, score + NOTHING, bombSignal});
            else if(grid[posx-1][posy+dx]==ENEMY){
               if(bombSignal == HAS_BOMB_SIGNAL){
                    q.push({posx-1, posy+dx, score+NOTHING, posx-1});
               }else{
                    if(bombSignal-BRANGE+1<=posx-1){
                        q.push({posx-1, posy+dx, score+NOTHING, bombSignal});
                    }else { // game ends
                        final_score = max(final_score, score);
                    }
               }
            }
        }
    }

    return final_score;
}