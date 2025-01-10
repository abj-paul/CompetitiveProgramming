#include<iostream>
#include<vector>
#include<climits>
using namespace std;

int min_distance_to_walk(int nSpots, vector<int>& gate_position, vector<int>& waiting);

int main(){
    int nSpots;
    cin>>nSpots;
    
    vector<int> position(4), waiting(4);
    for(int i=1; i<=3; i++) cin >> position[i];
    for(int i=1; i<=3; i++) cin >> waiting[i];

    cout << min_distance_to_walk(nSpots, position, waiting) << endl;

    return 0;
}

int min_distance_to_walk(int nSpots, vector<int>& gate_position, vector<int>& waiting){

    vector<int> starting_position(4), total_distance(4, INT_MAX);
    // Initialize
    int accumulator = 0;
    for(int i=3; i>=1; i--){
        accumulator+=waiting[i];
        starting_position[i] = nSpots - accumulator + 1;
    }

    int ans = INT_MAX;
    while(starting_position[1]>=1){
        for(int i=3; i>=1; i--){
            int curr_distance;
            if(starting_position[i]>gate_position[i]) { //right
                int maxDistance = (starting_position[i] + waiting[i]-1)-gate_position[i]+1;
                int minDistance = starting_position[i] - gate_position[i];
                curr_distance = (maxDistance*(maxDistance+1))/2 - (minDistance*(minDistance+1))/2;
            }else if(starting_position[i]+waiting[i]-1<=gate_position[i]){ //left
                int maxDistance = gate_position[i] - starting_position[i] + 1;
                int minDistance = gate_position[i] - (starting_position[i]+waiting[i]-1);
                curr_distance = (maxDistance*(maxDistance+1))/2 - (minDistance*(minDistance+1))/2;
            }else {
                int leftDistance = gate_position[i] - starting_position[i] + 1;
                int rightDistance = (starting_position[i] + waiting[i]-1) - gate_position[i] + 1;
                curr_distance = (leftDistance*(leftDistance+1))/2 + (rightDistance*(rightDistance+1))/2 - 1;
            }

            if(curr_distance<total_distance[i]){
                total_distance[i] = curr_distance;
                for(int j=i-1; j>=1; j--) total_distance[j] = INT_MAX;
            }
        }
        ans = min(ans, total_distance[1] + total_distance[2] + total_distance[3]);
        for(int i=1; i<=3; i++) starting_position[i]--;
    }

    return ans;
}