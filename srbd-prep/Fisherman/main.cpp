#include<bits/stdc++.h>
using namespace std;

const int NUM_GATES = 3;
const int MAX_POSITION = 25;

int N; //Number of fishing spots
int gate[MAX_POSITION] = {};
int fishermen[MAX_POSITION] = {}; // since each position has 1 fisherman

int spot_status[MAX_POSITION] = {};
int gateOrder[NUM_GATES] = {};
int visited[NUM_GATES] = {};

int minTotalDistance = INT_MAX;


void assignSpots(int spot_status[], int gateIndex){
    int currentGate = gateOrder[gateIndex];
    int gatePosition = gate[currentGate];
    int num_fisherman = fishermen[currentGate];

    int distance = 0;
    while(num_fisherman>0){ // Try on gate position
        if(distance == 0 && spot_status[gatePosition] == 0){
            spot_status[gatePosition] = 1;
            num_fisherman--;
            continue;
        }

        // Try on both sides of gate
        int leftSpot = gatePosition - distance;
        int rightSpot = gatePosition + distance;

        // Special case: When only one fisherman left, try both spots before committing
        if(leftSpot >=1 && rightSpot <= N && spot_status[leftSpot] == 0 && spot_status[rightSpot] == 0 && num_fisherman == 1){

            // Try left spot
            vector<int> tempSpots(spot_status, spot_status + MAX_POSITION);
            num_fisherman--;
            tempSpots[leftSpot] = distance + 1;
            assignSpots(tempSpots.data(), gateIndex + 1);

            // Try right spot
            spot_status[rightSpot] = distance + 1;
            assignSpots(spot_status, gateIndex + 1);
            return;
        }

        // Place fishermen in available spots
        if(leftSpot >=1 && spot_status[leftSpot] == 0 && num_fisherman > 0){
            spot_status[leftSpot] = distance + 1;
            num_fisherman--;
        }

        if(rightSpot <= N && spot_status[rightSpot] == 0 && num_fisherman  > 0){
            spot_status[rightSpot] = distance + 1;
            num_fisherman--;
        }
        distance++;
    }

    // If we have processed all gates, calcualte total distance
    if(gateIndex >= NUM_GATES){
        int totalDistance = 0;
        for(int i=1; i<=N; i++){
            totalDistance += spot_status[i];
        }
        minTotalDistance = min(minTotalDistance, totalDistance);
    } else assignSpots(spot_status, gateIndex + 1);
}


void generateGateOrders(int index){
    if(index > NUM_GATES){
        fill(spot_status + 1, spot_status + N + 1, 0);
        assignSpots(spot_status,1);
        return;
    }

    for(int i=1; i<= NUM_GATES; i++){
        if(!visited[i]){
            visited[i]=1;
            gateOrder[index]=i;
            generateGateOrders(index+1);
            visited[i] = 0;
        }
    }
}




int main(){
    cin>>N;

    for(int i=1; i<=3; i++) cin>>gate[i];
    for(int i=1; i<=3; i++) cin>>fishermen[i];
    generateGateOrders(1);
    cout << minTotalDistance <<endl;
}
