#include<bits/stdc++.h>
using namespace std;

const int MAX_GATES = 3;

// Function Prototypes
int get_minimum_distance(int num_fishing_spots, const vector<int>& gate_positions, const vector<int>& waiting_fishermen);
int generateGateOrder(int orderIndex, vector<int>& gateOrder, vector<int> visited_gates, int num_fishing_spots, const vector<int>& gate_positions, const vector<int>& waiting_fishermen);
int assignSpot(int gateIndex, const vector<int>& gateOrder, vector<int>& fishing_spot, int num_fishing_spots, const vector<int>& gate_positions, const vector<int>& waiting_fishermen);

int main() {
    int num_fishing_spots;
    cin >> num_fishing_spots;

    // Initialize vectors with size MAX_GATES + 1 to account for 1-based indexing
    vector<int> gate_positions(MAX_GATES + 1), waiting_fishermen(MAX_GATES + 1);
    for(int i = 1; i <= MAX_GATES; i++) cin >> gate_positions[i];
    for(int i = 1; i <= MAX_GATES; i++) cin >> waiting_fishermen[i];

    cout << get_minimum_distance(num_fishing_spots, gate_positions, waiting_fishermen);
    return 0;
}

int get_minimum_distance(int num_fishing_spots, const vector<int>& gate_positions, const vector<int>& waiting_fishermen) {
    vector<int> visited_gates(MAX_GATES + 1, 0);
    // Initialize gateOrder with size MAX_GATES + 1 for 1-based indexing
    vector<int> gateOrder(MAX_GATES + 1);
    return generateGateOrder(1, gateOrder, visited_gates, num_fishing_spots, gate_positions, waiting_fishermen);
}

int generateGateOrder(int orderIndex, vector<int>& gateOrder, vector<int> visited_gates, int num_fishing_spots, const vector<int>& gate_positions, const vector<int>& waiting_fishermen) {
    if(orderIndex > MAX_GATES) {
        vector<int> fishing_spot(num_fishing_spots + 1, 0);
        return assignSpot(1, gateOrder, fishing_spot, num_fishing_spots, gate_positions, waiting_fishermen);
    }

    int ans = INT_MAX;
    for(int i = 1; i <= MAX_GATES; i++) {
        if(!visited_gates[i]) {
            visited_gates[i] = 1;
            gateOrder[orderIndex] = i;
            // Fix: Increment orderIndex in recursive call
            ans = min(ans, generateGateOrder(orderIndex + 1, gateOrder, visited_gates, num_fishing_spots, gate_positions, waiting_fishermen));
            visited_gates[i] = 0;
        }
    }
    return ans;
}

int assignSpot(int gateIndex, const vector<int>& gateOrder, vector<int>& fishing_spot, int num_fishing_spots, const vector<int>& gate_positions, const vector<int>& waiting_fishermen) {
    if(gateIndex > MAX_GATES) {
        int totalDistance = 0;
        for(int i = 1; i <= num_fishing_spots; i++) {
            totalDistance += fishing_spot[i];
        }
        return totalDistance;
    }

    int currentGateNumber = gateOrder[gateIndex];
    int gatePosition = gate_positions[currentGateNumber];
    int num_fisherman = waiting_fishermen[currentGateNumber];
    
    int distance = 0;
    while(num_fisherman > 0) {
        // Try to place on gate position first
        if(distance == 0 && fishing_spot[gatePosition] == 0) {
            fishing_spot[gatePosition] = 1;
            num_fisherman--;
            distance++;
            continue;
        }

        int leftSpot = gatePosition - distance;
        int rightSpot = gatePosition + distance;

        // Handle special case when only 1 fisherman is left
        if(num_fisherman == 1 && leftSpot >= 1 && rightSpot <= num_fishing_spots && 
           fishing_spot[leftSpot] == 0 && fishing_spot[rightSpot] == 0) {
            // Try left first
            vector<int> temp_fishing_spots = fishing_spot;
            temp_fishing_spots[leftSpot] = distance + 1;
            int leftAns = assignSpot(gateIndex + 1, gateOrder, temp_fishing_spots, num_fishing_spots, gate_positions, waiting_fishermen);
            
            // Try right
            fishing_spot[rightSpot] = distance + 1;
            int rightAns = assignSpot(gateIndex + 1, gateOrder, fishing_spot, num_fishing_spots, gate_positions, waiting_fishermen);
            
            return min(leftAns, rightAns);
        }

        // Place on two sides based on distance
        if(leftSpot >= 1 && fishing_spot[leftSpot] == 0 && num_fisherman > 0) {
            fishing_spot[leftSpot] = distance + 1;
            num_fisherman--;
        }
        if(rightSpot <= num_fishing_spots && fishing_spot[rightSpot] == 0 && num_fisherman > 0) {
            fishing_spot[rightSpot] = distance + 1;
            num_fisherman--;
        }
        distance++;
    }

    return assignSpot(gateIndex + 1, gateOrder, fishing_spot, num_fishing_spots, gate_positions, waiting_fishermen);
}