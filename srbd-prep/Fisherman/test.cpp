#include <iostream>
#include <vector>
using namespace std;

// Constants
const int INF = 999999;
const int MAX_SIZE = 25;
const int NUM_GATES = 3;

// Global variables
int N;  // Number of fishing spots
int gate[MAX_SIZE] = {};    // Positions of gates
int human[MAX_SIZE] = {};   // Number of fishermen at each gate
int spots[MAX_SIZE] = {};   // Fishing spots occupation status
int gateOrder[MAX_SIZE] = {};  // Order in which gates are processed
int visited[MAX_SIZE] = {};    // Track visited gates in permutation
int minTotalDistance;          // Minimum total walking distance

/**
 * Places fishermen from a gate to available spots and calculates total distance
 * @param spots Current occupation status of fishing spots
 * @param gateIndex Current gate being processed in the permutation
 */
void assignSpots(int spots[], int gateIndex) {
    // Get current gate information
    int currentGate = gateOrder[gateIndex];
    int gatePosition = gate[currentGate];
    int fishermen = human[currentGate];
    
    // Try placing fishermen starting from gate position
    int distance = 0;
    while(fishermen > 0) {
        // Try placing at gate position first
        if(distance == 0 && spots[gatePosition] == 0) {
            spots[gatePosition] = 1;
            fishermen--;
            continue;
        }
        
        // Try spots on both sides of the gate
        int leftSpot = gatePosition - distance;
        int rightSpot = gatePosition + distance;
        
        // Special case: when only one fisherman left, try both spots before committing
        if(leftSpot >= 1 && rightSpot <= N && spots[leftSpot] == 0 && 
           spots[rightSpot] == 0 && fishermen == 1) {
            // Try left spot
            vector<int> tempSpots(spots, spots + MAX_SIZE);
            fishermen--;
            tempSpots[leftSpot] = distance + 1;
            assignSpots(tempSpots.data(), gateIndex + 1);
            
            // Try right spot
            spots[rightSpot] = distance + 1;
            assignSpots(spots, gateIndex + 1);
            return;
        }
        
        // Place fishermen in available spots
        if(leftSpot >= 1 && spots[leftSpot] == 0 && fishermen > 0) {
            spots[leftSpot] = distance + 1;
            fishermen--;
        }
        if(rightSpot <= N && spots[rightSpot] == 0 && fishermen > 0) {
            spots[rightSpot] = distance + 1;
            fishermen--;
        }
        
        distance++;
    }
    
    // If we've processed all gates, calculate total distance
    if(gateIndex >= NUM_GATES) {
        int totalDistance = 0;
        for(int i = 1; i <= N; i++) {
            totalDistance += spots[i];
        }
        minTotalDistance = min(minTotalDistance, totalDistance);
    } else {
        assignSpots(spots, gateIndex + 1);
    }
}

/**
 * Generates all possible gate opening orders using permutation
 * @param index Current position in permutation
 */
void generateGateOrders(int index) {
    if(index > NUM_GATES) {
        // Initialize spots array for new permutation
        fill(spots + 1, spots + N + 1, 0);
        assignSpots(spots, 1);
        return;
    }
    
    // Generate permutations
    for(int i = 1; i <= NUM_GATES; i++) {
        if(!visited[i]) {
            visited[i] = 1;
            gateOrder[index] = i;
            generateGateOrders(index + 1);
            visited[i] = 0;
        }
    }
}

int main() {
    // Input
    cin >> N;
    for(int i = 1; i <= NUM_GATES; i++) cin >> gate[i];
    for(int i = 1; i <= NUM_GATES; i++) cin >> human[i];
    
    // Solve
    minTotalDistance = INF;
    generateGateOrders(1);
    
    // Output
    cout << minTotalDistance << endl;
    
    return 0;
}