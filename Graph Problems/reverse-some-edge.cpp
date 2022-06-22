// https://www.codechef.com/problems/REVERSE

#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<queue>

#define PATH_WEIGHT 0
#define REVERSE_WEIGHT 1

int main(){

    int vertices,edges;
    std::cin>>vertices>>edges; 

    std::vector<std::pair<int, int>> graph[vertices];

    for(int i=0; i<edges; i++){
        int u, v;
        std::cin>>u>>v;
        graph[u].push_back({v, PATH_WEIGHT});

        // Adding reverse for solution
        graph[u].push_back({u, REVERSE_WEIGHT});
    }

    // Dijkstra Shortest Path Algorithm
    int source = 1, destination = vertices;
    std::vector<bool> visited(vertices, false);
    std::vector<int> distance(vertices, INT32_MAX);

    std::priority_queue<int> pq;

    visited[source] = true;
    distance[source] = 0;
    pq.push(source);

    while(~pq.empty()){
        

    }

    return 0;
}