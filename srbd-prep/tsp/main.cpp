#include<bits/stdc++.h>
using namespace std;

//Function Prototypes
int find_min_cost(const vector<vector<int>>& graph);
int tsp(int source, int mask, const vector<vector<int>>& graph,vector<vector<int>>& dp);


int main(){
    int number_of_test_cases;
    cin>>number_of_test_cases;

    for(int tc=1; tc<=number_of_test_cases; tc++){
        int number_of_cities;
        cin>>number_of_cities;

        vector<vector<int>> graph (number_of_cities, vector<int>(number_of_cities, 0));
        for(int i=0; i<number_of_cities; i++){
            for(int j=0; j<number_of_cities; j++){
                cin>>graph[i][j];
            }
        }

        cout<<find_min_cost(graph)<<endl;
    }
    return 0;
}

int find_min_cost(const vector<vector<int>>& graph){
    int n = graph.size();
    vector<vector<int>> dp(1<<n, vector<int>(n,-1));

    return tsp(0,1,graph,dp);
}

int tsp(int source, int mask, const vector<vector<int>>& graph,vector<vector<int>>& dp){
    int n = graph.size();
    if(mask==((1<<n)-1) ) return graph[source][0];
    if(dp[mask][source]!=-1) return dp[mask][source];

    int min_cost = INT_MAX;
    for(int loc=1; loc<n; loc++){
        if(!(mask & (1<<loc))){
            min_cost = min(min_cost, graph[source][loc] + tsp(loc, mask | 1<<loc, graph, dp));
        }
    }

    return dp[mask][source] = min_cost;
}