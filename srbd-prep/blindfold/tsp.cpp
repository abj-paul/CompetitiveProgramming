#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int HOME = 0;

// Function Prototypes
int min_cost_of_tour(int n, const vector<vector<int>> &graph);
int tsp(int curr_city, int mask, vector<vector<int>>& dp, const vector<vector<int>>& graph);


int main(){
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
        int num_of_cities,cost;
        cin>>num_of_cities;

        vector<vector<int>> graph (num_of_cities, vector<int>(num_of_cities, -1));
        for(int i=0; i<num_of_cities; i++){
            for(int j=0; j<num_of_cities; j++) cin>>graph[i][j];
        }

        cout << min_cost_of_tour(num_of_cities, graph) << endl;
    }
    return 0;
}

int min_cost_of_tour(int n, const vector<vector<int>>& graph){
    vector<vector<int>> dp(n, vector<int>(1<<n, 0));
    return tsp(HOME, 1, dp, graph);
}

int tsp(int curr_city, int mask, vector<vector<int>>& dp, const vector<vector<int>>& graph){
    int n = graph.size();
    if(mask == ((1<<n)-1))  return graph[curr_city][HOME];
    if(dp[curr_city][mask]) return dp[curr_city][mask];

    int min_cost = INT_MAX;
    for(int next_city = 1; next_city<n; next_city++){
        if(!(mask & (1<<next_city))){
            min_cost = min(min_cost, graph[curr_city][next_city] + tsp(next_city, mask | 1<<next_city, dp, graph));
        }
    }
    return dp[curr_city][mask]=min_cost;
}