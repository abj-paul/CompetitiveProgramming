#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
const int WHITE=0,GRAY=1,BLACK=2,PHI=-1;

vector<int> min_cycle;
int min_cost = INT_MAX;

void find_cycle_in_graph(const int nodes, const int edges, const vector<vector<int>>& adj);
void dfs(int node, vector<int>& visited, vector<int>& path, const vector<vector<int>>& adj);

int main(){
    int nodes,edges;
    cin>>nodes>>edges;

    int start,end;
    vector<vector<int>> adj (nodes+1);
    for(int i=0; i<edges; i++){
        cin>>start>>end;
        adj[start].push_back(end);
    }

    find_cycle_in_graph(nodes,edges,adj);

    for(int i=0; i<min_cycle.size(); i++) cout << min_cycle[i] << " ";
    cout<<endl;

    return 0;
}

void find_cycle_in_graph(const int nodes, const int edges, const vector<vector<int>>& adj){
    vector<int> visited (nodes+1, WHITE);
    vector<int> path (nodes+1, PHI);

    for(int i=1; i<visited.size(); i++){
        if(visited[i]==WHITE) {
            visited[i] = GRAY;
            dfs(i,visited,path,adj);
        }
    }
}

void dfs(int node, vector<int>& visited, vector<int>& path, const vector<vector<int>>& adj){
    if(node<0 || node>=adj.size()) return;

    for(int i=0; i<adj[node].size(); i++){
        int curr_node = adj[node][i];
        if(visited[curr_node]==GRAY){ //cycle detected
            vector<int> cycle;
            int cost = 0;
            int parent = node;
            cycle.push_back(curr_node);
            while(parent!=curr_node){
                cycle.push_back(parent);
                parent = path[parent];
            }
            sort(cycle.begin(), cycle.end());
            for(int j=0; j<cycle.size(); j++) cost+=cycle[j];
            if(cost<min_cost){
                min_cost = cost;
                min_cycle = cycle;
            }
        }else{
            visited[curr_node] = GRAY;
            path[curr_node] = node;
            dfs(curr_node, visited, path, adj);
        }
    }

    visited[node] = BLACK;
}
