#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

struct Coordinate {
    int x,y;
};

struct Warmhole{
    Coordinate left, right;
    int cost;
};

int find_min_distance_to_go_home(const Coordinate source, const Coordinate destination, const vector<Warmhole>& whs);
int dijkstra(int home, int destination, const vector<vector<int>>& graph);

int main(){
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
        int nWarmhole;
        cin>>nWarmhole;
        
        Coordinate source, destination;
        vector<Warmhole> whs (nWarmhole);
        cin>>source.x>>source.y>>destination.x>>destination.y;
        for(int i=0; i<nWarmhole; i++) cin>>whs[i].left.x>>whs[i].left.y>>whs[i].right.x>>whs[i].right.y>>whs[i].cost;

        cout << find_min_distance_to_go_home(source, destination, whs) << endl;
    }
    return 0;
}

int manhattan_distance(Coordinate A, Coordinate B){
    return abs(A.x-B.x) + abs(A.y-B.y);
}

int find_min_distance_to_go_home(const Coordinate source, const Coordinate destination, const vector<Warmhole>& whs){
    // create nodes
    vector<Coordinate> coords;
    coords.push_back(source);
    for(int i=0; i<whs.size(); i++){
        coords.push_back(whs[i].left);
        coords.push_back(whs[i].right);
    }
    coords.push_back(destination);

    // construct graph
    int n = coords.size();
    vector<vector<int>> graph(n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) graph[i][j] = manhattan_distance(coords[i], coords[j]);
    }

    // Updating with warmhole
    for(int i=1; i<n-1; i++){
        for(int j=1; j<n-1; j++){
            if(i%2==1) graph[i][j] = min(graph[i][j], whs[i/2].cost + graph[i+1][j]);
            else graph[i][j] = min(graph[i][j], whs[i/2-1].cost + graph[i-1][j]);
        }
    }

    return dijkstra(0,n-1, graph);
}

int dijkstra(int home, int destination, const vector<vector<int>>& graph){

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    vector<int> distances (graph.size(), INT_MAX);

    distances[home] = 0;
    q.push({0, home});

    while(!q.empty()){
        int distance = q.top().first, node = q.top().second;
        q.pop();
        
        for(int i=0; i<graph[node].size(); i++){
            int new_distance = distance + graph[node][i];
            if(new_distance < distances[i]){
                distances[i] = new_distance;
                q.push({new_distance, i});
            }
        }
    }


    return distances[destination];
}