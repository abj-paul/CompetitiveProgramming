#include<bits/stdc++.h>
using namespace std;

// Global Variables & Cosntants
const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;
int min_cost_of_cycle = INT_MAX;
vector<int> min_cost_cycle;

// Function Prototype
void dfs(int node, vector<vector<int>>& adj, vector<int>& visited, vector<int>& path);
void detect_cycle(vector<vector<int>>& adj, int nodes);

int main(){
    int nodes, edges;
    cin>>nodes>>edges;

    vector<vector<int>> adj(nodes+1);
    int u,v;
    for(int i=0; i<edges; i++) {
        cin>>u>>v;
        adj[u].push_back(v);
    }

    detect_cycle(adj, nodes);

    if(min_cost_cycle.empty()) cout<<"No cycle found."<<endl;
    else {
        for(int i=0; i<min_cost_cycle.size(); i++) cout << min_cost_cycle[i] << " ";
        cout<<endl;
    }
}

void detect_cycle(vector<vector<int>>& adj, int nodes){
    vector<int> visited(nodes+1, WHITE), path(nodes+1, -1);

    for(int i=1; i<=nodes; i++){
        if(visited[i]==WHITE){
            dfs(i, adj, visited, path);
        }
    }
}

void dfs(int node, vector<vector<int>>& adj, vector<int>& visited, vector<int>& path){
    visited[node] = GRAY;

    for(int neighbor: adj[node]){
        if(visited[neighbor]==WHITE){
            path[neighbor]=node;
            dfs(neighbor, adj, visited, path);
        }
        else if(visited[neighbor]==GRAY){
            //Cycle detected!!
            vector<int> cycle;
            int parent = node;
            int cost = neighbor;
            cycle.push_back(neighbor);
            while(parent!=neighbor){
                cost += cycle.back();
                cycle.push_back(parent);
                parent = path[parent];
            }

            if(min_cost_of_cycle>cost){
                sort(cycle.begin(), cycle.end());
                min_cost_cycle = cycle;
                min_cost_of_cycle = cost;
            }
        }
    }
    visited[node] = WHITE;
}