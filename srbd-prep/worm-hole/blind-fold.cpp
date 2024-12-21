#include<bits/stdc++.h>
using namespace std;

struct point {
    int x,y;
};

struct wormhole{
    point source, destination;
    int cost;
};

// Function Prototypes
int find_minimum_cost_to_travel(point source, point destination, const vector<wormhole>& whs);
int manhattan_distance(point A, point B);
int recursively_find_distance(point curr_source, point final_destination, const vector<wormhole>& whs, vector<int>& visited);

int main(){
    int test_cases, number_of_wormholes;
    cin>>test_cases;
    for(int tc=0; tc<test_cases; tc++){
        cin>>number_of_wormholes;

        point source, destination;
        cin>>source.x>>source.y>>destination.x>>destination.y;
        vector<wormhole> whs(number_of_wormholes);
        for(int i=0; i<number_of_wormholes; i++){
            cin>>whs[i].source.x>>whs[i].source.y;
            cin>>whs[i].destination.x>>whs[i].destination.y;
            cin>>whs[i].cost;
        }

        cout << find_minimum_cost_to_travel(source, destination, whs) << endl;
    }
    return 0;
}

int find_minimum_cost_to_travel(point source, point destination, const vector<wormhole>& whs){
    vector<int>visited (whs.size(), 0);

    return recursively_find_distance(source, destination, whs, visited);
}

int manhattan_distance(point A, point B){
    return abs(A.x-B.x) + abs(A.y-B.y);
}

int recursively_find_distance(point curr_source, point final_destination, const vector<wormhole>& whs, vector<int>& visited){
    int min_cost = INT_MAX;

    // Option 1: No wormhole usage
    min_cost = min(min_cost, manhattan_distance(curr_source, final_destination));

    // Option 2-3: Use bidirectional wormhole
    for(int i=0; i<whs.size(); i++){
        if(visited[i]) continue;
        visited[i] = 1;
        //Option 2: Forward Directional Wormhole
        min_cost = min(min_cost, manhattan_distance(curr_source, whs[i].source) + whs[i].cost + recursively_find_distance(whs[i].destination,final_destination,whs,visited)); // confusion

        //Option 3: Backward Directional Wormhole
        min_cost = min(min_cost,  manhattan_distance(curr_source, whs[i].destination) + whs[i].cost + recursively_find_distance(whs[i].source,final_destination,whs,visited)); // confusion

        visited[i] = 0;
    }

    return min_cost;
}