#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

const int WHITE=0, GRAY=1, BLACK=2, PHI = -1, STARTING_NODE=1;
vector<int> min_cycle;
int min_cost = INT_MAX;

void dfs(int curr_node, vector<int>& path, vector<int>& visited, const vector<vector<int>>& adj);
void find_min_cost_cycle(int nodes_count, int edges_count, const vector<vector<int>>& adj);

int main(){
    int nodes, edges, source, destination;
    cin>>nodes>>edges;
    vector<vector<int>> adj(nodes+STARTING_NODE);
    for(int i=0; i<edges; i++){
        cin >> source>>destination;
        adj[source].push_back(destination);
    }
    
    find_min_cost_cycle(nodes, edges, adj);
    for(int i=0; i<min_cycle.size(); i++) cout<<min_cycle[i]<<" ";
    cout<<endl;

    return 0;
}

void find_min_cost_cycle(int nodes_count, int edges_count, const vector<vector<int>>& adj){
    vector<int> visited (nodes_count+STARTING_NODE, WHITE);
    vector<int> path (nodes_count+STARTING_NODE, PHI);

    for(int i=STARTING_NODE; i<visited.size(); i++){
        if(visited[i]==WHITE) dfs(i,path,visited,adj);
    }
}

void dfs(int curr_node, vector<int>& path, vector<int>& visited, const vector<vector<int>>& adj){
    //cout <<"Exploring dfs for node "<<curr_node<<endl;
    for(int i=0; i<adj[curr_node].size(); i++){
        int neighbour = adj[curr_node][i];
        if(visited[neighbour]==GRAY){
            // Cycle detected
            int parent = curr_node;
            vector<int> temp_cycle;
            temp_cycle.push_back(neighbour);
            while(parent!=neighbour){
                temp_cycle.push_back(parent);
                parent = path[parent];
            }

            int sum = 0;
            for(int j=0; j<temp_cycle.size(); j++) sum+=temp_cycle[j];
            sort(temp_cycle.begin(), temp_cycle.end());

            if(sum<min_cost) min_cycle = temp_cycle;
        }else {
             visited[neighbour] = GRAY;
            path[neighbour] = curr_node;
            dfs(neighbour, path, visited, adj);
        }
    }

    visited[curr_node] = BLACK;
}
