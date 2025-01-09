#include<iostream>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

struct Coordinate {
    int x , y;
};

struct Warmhole {
    Coordinate point1, point2;
    int cost;
};

int dijkstra(int home, int final_desitnation, const vector<vector<int>>& graph);
int find_minimum_distance(int nWarmholes, Coordinate source, Coordinate destination, const vector<Warmhole>& whs);

int main(){
    int test_cases;
    cin>>test_cases;
    while(test_cases--){
        int nWarmholes;
        cin>>nWarmholes;
        Coordinate source, destination;
        cin>>source.x>>source.y>>destination.x>>destination.y;
        vector<Warmhole> whs (nWarmholes);
        for(int i=0; i<nWarmholes; i++){
            cin >> whs[i].point1.x>>whs[i].point1.y>>whs[i].point2.x>>whs[i].point2.y>>whs[i].cost;
        }

        cout << find_minimum_distance(nWarmholes, source, destination, whs) << endl;
    }
    return 0;
}

int manhattan_distance(Coordinate A, Coordinate B){
    return abs(A.x - B.x) + abs(A.y - B.y);
}

int find_minimum_distance(int nWarmholes, Coordinate source, Coordinate destination, const vector<Warmhole>& whs){
    // Lets make it a graph
    vector<Coordinate> coords;
    coords.push_back(source);
    for(int i=0; i<whs.size(); i++){
        coords.push_back(whs[i].point1);
        coords.push_back(whs[i].point2);
    }
    coords.push_back(destination);

    // Now lets make a graph
    vector<vector<int>> graph (coords.size(), vector<int>(coords.size()));
    for(int i=0; i<coords.size(); i++){
        for(int j=0; j<coords.size(); j++) graph[i][j] = manhattan_distance(coords[i], coords[j]);
    }

    for(int i=1; i<graph.size()-1; i++){
        for(int j=1; j<graph.size()-1; j++){
            if(i%2==1){
                graph[i][j] =  min(graph[i][j], whs[i/2].cost + graph[i+1][j]);
            }else {
                graph[i][j] =  min(graph[i][j], whs[i/2-1].cost + graph[i-1][j]);
            }
        }
    }

    return dijkstra(0, graph.size()-1, graph);
}

int dijkstra(int home, int final_desitnation, const vector<vector<int>>& graph){
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    vector<bool> visited (graph.size(), false);

    q.push({0,home});
    
    while(!q.empty()){
        int cost = q.top().first, node = q.top().second;
        q.pop();
        visited[node] = true;

        if(node==final_desitnation) return cost;

        for(int neighbour=0; neighbour<graph[node].size(); neighbour++){
            if(!visited[neighbour]){
                int new_cost = cost + graph[node][neighbour];
                q.push({new_cost, neighbour});
            }
        }
    }
    return -1;
}