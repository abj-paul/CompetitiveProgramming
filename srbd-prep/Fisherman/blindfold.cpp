#include<bits/stdc++.h>
using namespace std;

const int MAX_GATE = 3;

// Function Prototypes
int find_minimum_distance_for_fishermen(int num_of_fishing_spots, const vector<int>& gates_position, const vector<int>& fishermen_number);
int generate_gate_orders(int orderIndex, vector<int>& gates_order, vector<int>& visited_gates, int num_of_fishing_spots, const vector<int>& gates_position, const vector<int>& fishermen_number);
int assignFishingSpot(int gateIndex, vector<int>& gates_order, int num_of_fishing_spots, vector<int>& fishing_spots, const vector<int>& gates_position, const vector<int>& fishermen_number);

int main(){
    int num_of_fishing_spots;
    cin>>num_of_fishing_spots;

    vector<int> gates_position(MAX_GATE+1), fishermen_number(MAX_GATE+1);
    for(int i=1; i<=MAX_GATE; i++) cin>>gates_position[i];
    for(int i=1; i<=MAX_GATE; i++) cin>>fishermen_number[i];

    cout << find_minimum_distance_for_fishermen(num_of_fishing_spots, gates_position, fishermen_number) <<endl;
    return 0;
}

int find_minimum_distance_for_fishermen(int num_of_fishing_spots, const vector<int>& gates_position, const vector<int>& fishermen_number){
    vector<int> visited_gates(MAX_GATE+1, 0), gates_order(MAX_GATE+1);

    return generate_gate_orders(1, gates_order, visited_gates, num_of_fishing_spots, gates_position, fishermen_number);
}

int generate_gate_orders(int orderIndex, vector<int>& gates_order, vector<int>& visited_gates, int num_of_fishing_spots, const vector<int>& gates_position, const vector<int>& fishermen_number){
    int ans = 100;
    if(orderIndex>MAX_GATE){
        vector<int> fishing_spots(num_of_fishing_spots+1,0);
        int temp = assignFishingSpot(1, gates_order, num_of_fishing_spots, fishing_spots, gates_position, fishermen_number);
        ans = min(ans,temp);
        return ans;
    }

    for(int i=1; i<=MAX_GATE; i++){
        if(!visited_gates[i]){
            visited_gates[i] = 1;
            gates_order[orderIndex] = i;
            ans = min(ans,generate_gate_orders(orderIndex+1, gates_order, visited_gates, num_of_fishing_spots, gates_position, fishermen_number));
            visited_gates[i] = 0;
        }
    }

    return ans;
}

int assignFishingSpot(int gateIndex, vector<int>& gates_order, int num_of_fishing_spots, vector<int>& fishing_spots, const vector<int>& gates_position, const vector<int>& fishermen_number){
    int ans = INT_MAX;

    int gateNumber = gates_order[gateIndex];
    int gatePosition = gates_position[gateNumber];
    int num_fishermen = fishermen_number[gateNumber];

    int distance = 0;
    while(num_fishermen>0){
        // if gate spot is empty
        if(fishing_spots[gatePosition]==0){
            fishing_spots[gatePosition] = distance + 1;
            distance++;
            num_fishermen--;
            continue;
        }

        int leftSpot = gatePosition - distance;
        int rightSpot = gatePosition + distance;

        // special case: 1 fisherman left
        if(num_fishermen==1 && fishing_spots[leftSpot]==0 && fishing_spots[rightSpot]==0 && leftSpot>=1 && rightSpot<=num_of_fishing_spots){
            // Try left first
            vector<int> temp_fishing_spots (fishing_spots.begin(), fishing_spots.end());
            temp_fishing_spots[leftSpot] = distance + 1;
            int leftAns = assignFishingSpot(gateIndex+1, gates_order, num_of_fishing_spots, temp_fishing_spots, gates_position, fishermen_number);
            // Then try right
            fishing_spots[rightSpot] = distance + 1;
            int rightAns = min(ans, assignFishingSpot(gateIndex+1, gates_order, num_of_fishing_spots, fishing_spots, gates_position, fishermen_number));

            num_fishermen--;

            return min(ans, min(leftAns, rightAns));
        }

        // try left and right
        if(leftSpot>=1 && fishing_spots[leftSpot]==0){
            fishing_spots[leftSpot] = distance + 1;
            num_fishermen--;
        }
        if(rightSpot<=num_of_fishing_spots && fishing_spots[rightSpot]==0){
            fishing_spots[rightSpot] = distance + 1;
            num_fishermen--;
        }
        distance++;
    }

    if(gateIndex > MAX_GATE){ // All fisherment assigned, lets calculate total distance!
        int totalDistance = 0;
        for(int i=1; i<fishing_spots.size(); i++) totalDistance+=fishing_spots[i];
        return min(ans, totalDistance);
    } else return assignFishingSpot(gateIndex+1, gates_order, num_of_fishing_spots, fishing_spots, gates_position, fishermen_number);
}