#include<bits/stdc++.h>
using namespace std;

struct point {
    int x,y;
};
struct wormhole {
    point source, destination;
    int value;
};

// Function Prototypes
int find_minimum_cost_to_travel(point source, point destination, const vector<wormhole>& wormholes);
int manhattan_distance(point a, point b);
int solve(point source, int cost, point final_destination, const vector<wormhole>& wormholes, vector<int>& visited);


int main(){
    int num_of_test_cases, num_of_worm_holes;
    cin>>num_of_test_cases;

    for(int i=0; i<num_of_test_cases; i++){
        cin>>num_of_worm_holes;
        point source, destination;
        cin>>source.x>>source.y>>destination.x>>destination.y;

        vector<wormhole> wormholes (num_of_worm_holes);
        for(int i=0; i<num_of_worm_holes; i++){
            cin>>wormholes[i].source.x>>wormholes[i].source.y;
            cin>>wormholes[i].destination.x>>wormholes[i].destination.y;
            cin>>wormholes[i].value;
        }

        cout << find_minimum_cost_to_travel(source, destination, wormholes) << endl;
    }

    return 0;
}

int find_minimum_cost_to_travel(point source, point destination, const vector<wormhole>& wormholes){
    int n = wormholes.size();
    vector<int> visited(n, 0);

    return solve(source, 0, destination, wormholes, visited);
}


int manhattan_distance(point a, point b){
    return abs(a.x-b.x)+abs(a.y-b.y);
}

int solve(point source, int cost, point final_destination, const vector<wormhole>& wormholes, vector<int>& visited){
    int ans = cost + manhattan_distance(source, final_destination); // I can simply go or

    for(int i=0; i<wormholes.size(); i++){ // I can use one of the wormholes!
        if(!visited[i]){
            visited[i]=1;
            //Forward Direction
            ans = min(ans, solve(wormholes[i].destination, cost +  manhattan_distance(source, wormholes[i].source) + wormholes[i].value, final_destination, wormholes, visited));
            //Backward Direction
            ans = min(ans, solve(wormholes[i].source, cost + manhattan_distance(source, wormholes[i].destination) + wormholes[i].value, final_destination, wormholes, visited));
            visited[i]=0;
        }
    }

    cout<<"("<<source.x<<","<<source.y<<") -> ("<<final_destination.x<<","<<final_destination.y<<") ="<<ans<<endl;

    return ans;
}