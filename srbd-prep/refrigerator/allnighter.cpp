#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct Coordinate {
    int x, y;
};

const int PHI = -1;
int tsp(int curr_node, int mask, vector<vector<int>>& dp, const vector<vector<int>>& graph);
int find_minimum_traveling_distance(const Coordinate home, const Coordinate office, const vector<Coordinate>& drop_locations);

int main(){
    for(int tc=1; tc<=10; tc++){
        int nRefrigerator;
        cin>>nRefrigerator;
        vector<Coordinate> drop_locations (nRefrigerator);
        Coordinate home, office;
        cin>>office.x>>office.y>>home.x>>home.y;
        for(int i=0; i<nRefrigerator; i++) cin>>drop_locations[i].x>>drop_locations[i].y;

        cout<<"# "<<tc<<" "<<find_minimum_traveling_distance(home,office,drop_locations)<<endl;
    }

    return 0;
}

int manhattan_distance(Coordinate A, Coordinate B){
    return abs(A.x-B.x) + abs(A.y-B.y);
}

int find_minimum_traveling_distance(const Coordinate home, const Coordinate office, const vector<Coordinate>& drop_locations){
    // create nodes
    vector<Coordinate> coords;
    coords.push_back(office);
    for(int i=0; i<drop_locations.size(); i++) coords.push_back(drop_locations[i]);
    coords.push_back(home);

    // construct graph
    int n = coords.size();
    vector<vector<int>> graph(n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) graph[i][j] = manhattan_distance(coords[i], coords[j]);
    }

    //debug
    // cout<<"Printing Graph"<<endl;
    // for(int i=0; i<graph.size(); i++){
    //     for(int j=0; j<graph[i].size(); j++) cout << graph[i][j] << " ";
    //     cout<<endl;
    // }

    vector<vector<int>> dp(n, vector<int>(1<<n, PHI));
    return tsp(0,1,dp,graph);
}

int tsp(int curr_node, int mask, vector<vector<int>>& dp, const vector<vector<int>>& graph){
    //cout << "Traversing node "<<curr_node<<" with cost "<<cost<<endl;
    int n = graph.size()-1;
    if(mask == ((1<<n)-1)) return graph[curr_node][n];
    if(dp[curr_node][mask]!=PHI) return dp[curr_node][mask];
    
    int min_cost = INT_MAX;
    for(int i=1; i<n; i++){
        if(!(mask & 1<<i)){
            min_cost = min(min_cost, graph[curr_node][i] + tsp(i, mask | 1<<i , dp, graph));
        }
    }

    return dp[curr_node][mask] = min_cost;
}
