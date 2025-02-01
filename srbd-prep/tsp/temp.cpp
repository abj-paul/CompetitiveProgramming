#include<iostream>
#include<vector>
#include<climits>

using namespace std;

const int PHI = -1;
int tsp(int curr_city, int mask, vector<vector<int>>& dp, const vector<vector<int>>& graph);

int main(){
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
        int nCities;
        cin>>nCities;
        vector<vector<int>> graph (nCities, vector<int>(nCities));
        for(int i=0; i<nCities; i++){
            for(int j=0; j<nCities; j++) cin>>graph[i][j];
        }

        vector<vector<int>> dp(nCities, vector<int>(1<<nCities, PHI));
        cout << tsp(0,1,dp,graph) << endl;
    }
    return 0;
}
int tsp(int curr_city, int mask, vector<vector<int>>& dp, const vector<vector<int>>& graph){
    int n = graph.size();
    if(mask==(1<<n)-1) return graph[curr_city][0];
    if(dp[curr_city][mask]!=PHI) return dp[curr_city][mask];

    int min_cost = INT_MAX;
    for(int i=1; i<n; i++){
        if(!(mask & 1<<i)){
            min_cost = min(min_cost, graph[curr_city][i]+tsp(i, mask | 1<<i, dp, graph));
        }
    }
    return dp[curr_city][mask] = min_cost;
}