#include <bits/stdc++.h>
using namespace std;

const int BLACK = 2; // Fully processed
const int GRAY = 1;  // Processing
const int WHITE = 0; // Unvisited

// Global Variables
int min_cost_of_cycle = 1e5 + 1;
vector<int> min_cost_cycle;

// Function Prototypes
bool detect_cycle(int nodes, vector<vector<int>>& adj);
void dfs(int node, vector<int>& visited, vector<vector<int>>& adj, vector<int>& path);

int main() {
    int nodes, edges;
    cin >> nodes >> edges;

    vector<vector<int>> adj(nodes + 1);
    int u, v;

    for (int i = 0; i < edges; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
    }

    detect_cycle(nodes, adj);

    if (min_cost_cycle.empty()) {
        cout << "No Cycle" << endl;
    } else {
        for (int i = 0; i < min_cost_cycle.size(); i++) {
            cout << min_cost_cycle[i] << " ";
        }
        cout << endl;
    }
}

bool detect_cycle(int nodes, vector<vector<int>>& adj) {
    vector<int> visited(nodes + 1, WHITE);
    vector<int> path(nodes + 1, -1);

    for (int i = 1; i <= nodes; i++) {
        if (visited[i] == WHITE) {
            dfs(i, visited, adj, path);
        }
    }

    return !min_cost_cycle.empty();
}

void dfs(int node, vector<int>& visited, vector<vector<int>>& adj, vector<int>& path) {
    visited[node] = GRAY;

    for (int neighbour : adj[node]) {
        if (visited[neighbour] == WHITE) {
            path[neighbour] = node;
            dfs(neighbour, visited, adj, path);
        } else if (visited[neighbour] == GRAY) {
            // Cycle detected
            vector<int> cycle;
            int cost = 0;
            cycle.push_back(neighbour);
            cost += neighbour;

            int current = node;
            while (current != neighbour) {
                cycle.push_back(current);
                cost += current;
                current = path[current];
            }

            sort(cycle.begin(), cycle.end());

            if (cost < min_cost_of_cycle) {
                min_cost_of_cycle = cost;
                min_cost_cycle = cycle;
            }
        }
    }

    visited[node] = BLACK; // Fully processed
}
