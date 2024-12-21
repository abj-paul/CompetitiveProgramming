#include<bits/stdc++.h>
using namespace std;

// Function Prototypes
int manhattan_distance(pair<int,int> A, pair<int,int> B);
int find_minimum_distance(const vector<pair<int,int>>& coordinates);
int find_cost(int mask, int source, vector<vector<int>>& dp, const vector<vector<int>>& graph);


int main(){
    const int TEST_CASES = 10;
    for(int tc=1; tc<=TEST_CASES; tc++){
        int number_of_customers,x,y;
        cin>>number_of_customers;
        number_of_customers+=2;

        vector<pair<int,int>> coordinates(number_of_customers);
        cin>>x>>y;
        coordinates[0] = {x,y};
        cin>>x>>y;
        coordinates[number_of_customers-1] = {x,y};

        for(int i=1; i<number_of_customers-1; i++){
            cin>>x>>y;
            coordinates[i] = {x,y};
        }

        cout <<"# "<<tc<<" "<<find_minimum_distance(coordinates) << endl;
    }
    return 0;
}

int find_minimum_distance(const vector<pair<int,int>>& coordinates){
    int n = coordinates.size(), distance=0;
    vector<vector<int>> graph(n, vector<int> (n,0));

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            distance = manhattan_distance(coordinates[i], coordinates[j]);
            graph[i][j] = distance;
            graph[j][i] = distance;
        }
    }

    vector<vector<int>> dp(1<<n, vector<int> (n,-1));

    return find_cost(1,0, dp, graph);
}

int manhattan_distance(pair<int,int> A, pair<int,int> B){
    return abs(A.first-B.first) + abs(A.second - B.second);
}

int find_cost(int mask, int source, vector<vector<int>>& dp, const vector<vector<int>>& graph){
    int n = graph.size();
    
    if(mask==((1<<n)-1)) return graph[source][n-1]; // All traversed
    

    if(dp[mask][source]!=-1) return dp[mask][source];

    int cost = INT_MAX;
    for(int loc=0; loc<n; loc++){
        if (!(mask & (1 << loc))) {
            cost = min(cost, find_cost((mask|(1<<loc)), loc, dp, graph) + graph[source][loc]);
        }
    }

    return dp[mask][source] = cost;
}