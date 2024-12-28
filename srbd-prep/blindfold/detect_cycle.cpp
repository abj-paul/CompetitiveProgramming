#include<iostream>
#include<climits>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

const int STARTING_NODE = 1;
const int UNVISITED = -1, VISITED = 1;

vector<int> min_cost_cycle;
int min_cost_of_cycle=INT_MAX;

// Function Prototypes
void find_cycle_with_min_cost(int node_count, int edge_count, const vector<vector<int>>& adj);
void recursive_dfs(int curr_node, vector<int>& path, vector<int>& dfsvisited, vector<int>& visited, const vector<vector<int>>& adj);


int main(){
    int node_count, edge_count, u , v;
    cin>>node_count>>edge_count;

    vector<vector<int>> adj (node_count+STARTING_NODE);
    for(int i=0; i<node_count; i++) {
        cin>>u>>v;
        adj[u].push_back(v);
    }

    find_cycle_with_min_cost(node_count, edge_count, adj);
    for(int i=0; i<min_cost_cycle.size(); i++) cout<<min_cost_cycle[i]<<" ";
    cout<<endl;
    return 0;
}

void find_cycle_with_min_cost(int node_count, int edge_count, const vector<vector<int>>& adj){
    vector<int> visited(node_count+1, UNVISITED), dfsvisited(node_count+1, UNVISITED);
    for(int i=STARTING_NODE; i<adj.size(); i++){
        if(visited[i]==UNVISITED){
            vector<int> path(node_count+1, -1);
            recursive_dfs(i, path, dfsvisited, visited, adj);
        }
    }
    
}

void recursive_dfs(int curr_node, vector<int>& path, vector<int>& dfsvisited, vector<int>& visited, const vector<vector<int>>& adj){

    if(dfsvisited[curr_node]==VISITED){ // Cycle Detected
        vector<int> cycle;
        int parent = path[curr_node], cost=0;
        cycle.push_back(curr_node);
        while(parent!=curr_node && parent!=-1){
            cycle.push_back(parent);
            parent = path[parent];
        }
        for(int i=0; i<cycle.size(); i++) cost+=cycle[i];
        if(cost<min_cost_of_cycle){
            min_cost_of_cycle = cost;
            min_cost_cycle = cycle;
            sort(min_cost_cycle.begin(), min_cost_cycle.end());
            return;
        }
    }
    if(dfsvisited[curr_node]==VISITED) return;
    dfsvisited[curr_node] = VISITED;


    for(int neighbor: adj[curr_node]){
        if(visited[neighbor]==UNVISITED){
            path[neighbor] = curr_node;
            recursive_dfs(neighbor, path, dfsvisited, visited, adj);
        }
    }
    dfsvisited[curr_node] = UNVISITED;
    visited[curr_node] = VISITED;
}

