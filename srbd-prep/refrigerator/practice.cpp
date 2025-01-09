#include<iostream>
#include<vector>
#include<climits>
using namespace std;

struct Coordinate {
    int x , y;
};

const int PHI = -1;

int tsp(int curr_pos, int mask, vector<vector<int>>& dp, const vector<vector<int>>& graph);
int min_traversal(const int nRefrigerator, const Coordinate office,const Coordinate home, const vector<Coordinate>& drop_locations);


int main(){
    for(int tc=1; tc<=10; tc++){
        int nRefrigerator;
        cin>>nRefrigerator;

        Coordinate office,home;
        vector<Coordinate> drop_locations(nRefrigerator);
        cin>>office.x>>office.y;
        cin>>home.x>>home.y;
        for(int i=0; i<nRefrigerator; i++) cin>>drop_locations[i].x >> drop_locations[i].y;

        cout<<"# "<<tc<<" "<<min_traversal(nRefrigerator, office, home, drop_locations) << endl;
    }

    return 0;
}

int manhattan_distance(Coordinate A, Coordinate B){
    return abs(A.x - B.x) + abs(A.y - B.y);
}

int min_traversal(const int nRefrigerator, const Coordinate office,const Coordinate home, const vector<Coordinate>& drop_locations){
    vector<Coordinate> coordinates;
    coordinates.push_back(office);
    for(int i=0; i<drop_locations.size(); i++) coordinates.push_back(drop_locations[i]);
    coordinates.push_back(home);

    // Constructing graph
    int n = coordinates.size();
    vector<vector<int>> graph (n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) graph[i][j] = manhattan_distance(coordinates[i], coordinates[j]);
    }

    vector<vector<int>> dp(n, vector<int>(1<<n, PHI));

    return tsp(0, 1, dp, graph);
}

int tsp(int curr_pos, int mask, vector<vector<int>>& dp, const vector<vector<int>>& graph){
    //cout << "Travering TSP for drop position "<<curr_pos<<endl;
    int n = graph.size()-1;
    if(mask==(1<<n)-1) return graph[curr_pos][n];
    if(dp[curr_pos][mask]!=PHI) return dp[curr_pos][mask];

    int min_distance = INT_MAX;
    for(int i=1; i<n; i++){
        if(!(mask & (1<<i))){   
            min_distance = min(min_distance, graph[curr_pos][i] + tsp(i, mask | 1<<i, dp, graph));
        }
    }

    return dp[curr_pos][mask] = min_distance;
}