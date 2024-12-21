#include<bits/stdc++.h>
using namespace std;

// Function Prototype
int tsp(int source, int mask, const vector<vector<int>>& graph, vector<vector<int>>& dp);
int manhattan_distanc(pair<int,int> A, pair<int,int>B);
int find_minimum_travel_for_salesman(const vector<pair<int,int>>& coordinates, int n);

void util_print_matrix(const vector<vector<int>>& matrix, string title);
int main(){
    int num_of_test_cases=10;
    for(int tc=1; tc<=num_of_test_cases; tc++){
        int n,x,y;
        cin>>n;

        vector<pair<int,int>> coordinates (n+2);
        n+=2;
        cin>>x>>y;
        coordinates[0] = {x,y};
        cin>>x>>y;
        coordinates[n-1] = {x,y};
        for(int i=1; i<n-1; i++){
            cin>>x>>y;
            coordinates[i] = {x,y};
        }

        cout << "# "<<tc<<" "<<find_minimum_travel_for_salesman(coordinates,n) <<endl;
    }
    return 0;
}

int manhattan_distanc(pair<int,int> A, pair<int,int>B){
    return abs(A.first-B.first) + abs(A.second - B.second);
}

int find_minimum_travel_for_salesman(const vector<pair<int,int>>& coordinates, int n){
    vector<vector<int>> graph (n, vector<int> (n,0));
    
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int distance = manhattan_distanc(coordinates[i], coordinates[j]);
            graph[i][j] = distance;
            graph[j][i] = distance;
        }
    }

    vector<vector<int>> dp (1<<n, vector<int>(n, -1));
    //util_print_matrix(graph, "Graph");
    int temp = tsp(0,1,graph,dp);
    //util_print_matrix(dp, "DP");
    return temp;
}

void util_print_matrix(const vector<vector<int>>& matrix, string title){
    cout<<"Printing "<<title<<endl;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int tsp(int source, int mask, const vector<vector<int>>& graph, vector<vector<int>>& dp){
    int n = graph.size();
    if(mask == ((1<<n)-1) ) return graph[source][n-1]; // Go back home if finished!
    if(dp[mask][source]!=-1) return dp[mask][source];

    int min_cost = INT_MAX;
    for(int loc=1; loc<n; loc++){
        if(!(mask & (1<<loc))){
            min_cost = min(min_cost, graph[source][loc] + tsp(loc, mask | (1<<loc), graph, dp));
        }
    }

    //cout<<"Debug: "<<source<<" = "<<min_cost<<endl;
    return dp[mask][source] = min_cost;
}