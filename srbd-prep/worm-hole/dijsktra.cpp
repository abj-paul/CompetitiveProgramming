#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

const int PHI = -1;

struct coordinate {
    int x,y;
};

struct wormhole {
    coordinate source, destination;
    int cost;
};

// Function Prototypes
int find_min_cost_to_travel(coordinate source, coordinate destination, const vector<wormhole>& whs);
int dijkstra(const int source_node, const int destination_node, const vector<vector<int>>& graph);

int main(){
    int test_cases;
    cin>>test_cases;
    
    while(test_cases--){
        int nwhs;
        coordinate source,destination;
        cin>>nwhs;
        cin>> source.x >>source.y >> destination.x>>destination.y;

        vector<wormhole> whs(nwhs);
        for(int i=0; i<nwhs; i++) cin >> whs[i].source.x >> whs[i].source.y >> whs[i].destination.x >> whs[i].destination.y >> whs[i].cost;

        //for(int i=0; i<whs.size(); i++) cout<<"("<<whs[i].source.x << ","<<whs[i].source.y<<") --> ("<<whs[i].destination.x<<", "<<whs[i].destination.y<<"), ";
        //cout<<endl;
        
        cout << find_min_cost_to_travel(source, destination, whs) << endl;
    }

    return 0;
}

int manhattan_distance(coordinate A, coordinate B){
    return abs(A.x-B.x) + abs(A.y-B.y);
}

void print_graph(const vector<vector<int>>& graph){
    for(int i=0; i<graph.size(); i++){
        for(int j=0; j<graph.size(); j++) cout<<graph[i][j]<<" ";
        cout<<endl;
    }
}

int find_min_cost_to_travel(coordinate source, coordinate destination, const vector<wormhole>& whs){
    int n = whs.size()*2 + 2; //source, desintation
    vector<coordinate> temp_coordinates;
    temp_coordinates.push_back(source);
    for(int i=0; i<whs.size(); i++) {
        temp_coordinates.push_back(whs[i].source);
        temp_coordinates.push_back(whs[i].destination);
    }
    temp_coordinates.push_back(destination);
    

    vector<vector<int>> graph (n,vector<int>(n, PHI));
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) graph[i][j] = manhattan_distance(temp_coordinates[i], temp_coordinates[j]);
    }

    // Updating based on worm hole
    for(int i=1; i<n-1; i++){ // Because 0 and n-1 are source, desintation. They are not wormholes.
        for(int j=1; j<n-1; j++){
            if(i%2==1){
                graph[i][j] = min(graph[i][j], whs[i/2].cost + graph[i+1][j]);
            } else {
                graph[i][j] = min(graph[i][j], whs[(i/2)-1].cost + graph[i-1][j]);
            }
        }
    }

    //for(int i=0; i<temp_coordinates.size(); i++) cout<<"("<<temp_coordinates[i].x << ","<<temp_coordinates[i].y<<"), ";
    //cout<<endl;
    //print_graph(graph);

    return dijkstra(0, n-1, graph);
}

int dijkstra(const int source_node, const int destination_node, const vector<vector<int>>& graph){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    int n = graph.size();

    vector<int> distance(n,INT_MAX);
    vector<bool> processed(n, false);

    q.push({0, source_node});
    processed[0] = true;
    distance[0] = 0;

    while(!q.empty()){
        int d = q.top().first, node=q.top().second;
        q.pop();

        for(int i=0; i<n; i++){
            if(!processed[i]){
                int new_dist = d+graph[node][i];
                if(new_dist < distance[i]){
                    distance[i] = new_dist;
                    q.push({new_dist, i});
                }
            }
        }
    }

    return distance[destination_node];

}