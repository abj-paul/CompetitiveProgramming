#include<iostream>
#include<climits>
#include<vector>
#include<queue>

using namespace std;

struct coordinate {
    int x,y;
};

struct wormhole {
  coordinate source, destination;
  int cost;  
};

// Function Prototypes
int dijsktra(int start, int end, const vector<vector<int>>& graph);
int find_min_distance_via_wormholes(coordinate start, coordinate end, int num_wormholes, const vector<wormhole>& whs);

int main(){
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
        int num_wormholes;
        cin>>num_wormholes;

        coordinate start, end;
        cin>>start.x>>start.y>>end.x>>end.y;

        vector<wormhole> whs(num_wormholes);
        for(int i=0; i<whs.size(); i++){
            cin>>whs[i].source.x>>whs[i].source.y>>whs[i].destination.x>>whs[i].destination.y>>whs[i].cost;
        }

        cout << find_min_distance_via_wormholes(start, end, num_wormholes, whs) << endl;
    }
}

int manhattan_distance(coordinate A, coordinate B) {
    return abs(A.x-B.x) + abs(A.y-B.y);
}

int find_min_distance_via_wormholes(coordinate start, coordinate end, int num_wormholes, const vector<wormhole>& whs){
    int n = whs.size()*2 + 2; //source, destination
    vector<coordinate> temp_coordinates;
    temp_coordinates.push_back(start);
    for(int i=0; i<whs.size(); i++) {
        temp_coordinates.push_back(whs[i].source);
        temp_coordinates.push_back(whs[i].destination);
    }
    temp_coordinates.push_back(end);

    // Constructing GRID
    vector<vector<int>> graph (n, vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) graph[i][j] = manhattan_distance(temp_coordinates[i], temp_coordinates[j]);
    }

    // Updating based on wormhole usage
    for(int i=1; i<n-1; i++){
        for(int j=0; j<n; j++){
            if(i%2==1) graph[i][j] = min(graph[i][j], whs[i/2].cost + graph[i+1][j]);
            else graph[i][j] = min(graph[i][j], whs[i/2-1].cost + graph[i-1][j]);
        }
    }

    return dijsktra(0, n-1, graph);
}

int dijsktra(int start, int end, const vector<vector<int>>& graph){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    vector<int> distance(graph.size(), INT_MAX);
    vector<int> visited(graph.size(), false);

    q.push({0,start});
    distance[0] = 0;

    while(!q.empty()){
        int d = q.top().first, curr_node = q.top().second;
        q.pop();
        visited[curr_node] = true;
        //cout<<"Dequeueing "<<curr_node<<endl;
        if(curr_node==end) return d;

        for(int i=0; i<graph[curr_node].size(); i++){
            if(!visited[i]){
                int new_dist = d + graph[curr_node][i];
                q.push({new_dist, i});
            }
        }
    }

    return -1;
}