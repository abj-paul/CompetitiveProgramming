#include<iostream>
#include<vector>
#include<climits>
using namespace std;

const int PHI = -1;
int find_min_distance_for_traveling(const int nCities,const vector<vector<int>>& grid);
int tsp(int curr_city, int mask, vector<vector<int>>& dp, const vector<vector<int>>& grid);

int main(){
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
        int nCities;
        cin>>nCities;
        vector<vector<int>> grid(nCities, vector<int>(nCities));
        for(int i=0; i<nCities; i++){
            for(int j=0; j<nCities; j++) cin>>grid[i][j];
        }

        cout << find_min_distance_for_traveling(nCities, grid) << endl;
    }
    return 0;
}

int find_min_distance_for_traveling(const int nCities,const vector<vector<int>>& grid){
    if(nCities==1) return 0;
    vector<vector<int>> dp (nCities, vector<int>(1<<nCities, PHI));

    return tsp(0, 1 ,dp, grid);
}

int tsp(int curr_city, int mask, vector<vector<int>>& dp, const vector<vector<int>>& grid){
    int n = grid.size();
    if(mask==(1<<n)-1) return grid[curr_city][0]; // reached destintation
    if(curr_city<0 || curr_city>=n) return 0;
    if(dp[curr_city][mask]!=PHI) return dp[curr_city][mask];

    int min_distance = INT_MAX;
    for(int i=0; i<n; i++){
        if(!(mask & (1<<i))){
            min_distance = min(min_distance,  grid[curr_city][i] + tsp(i, mask | (1<<i), dp, grid));
        }
    }
    return dp[curr_city][mask] = min_distance;
}