#include<iostream>
#include<vector>
#include<climits>

using namespace std;

const int NGATES = 3, STARTING_POS = 1;

int find_min_distance_for_fisherment(const int n_fishing_spot, const vector<int>& gates_position, const vector<int>& waiting);

int main(){
    int n_fishing_spot;
    cin>>n_fishing_spot;

    vector<int> gates_position(NGATES+STARTING_POS), waiting(NGATES+STARTING_POS);
    for(int i=STARTING_POS; i<=NGATES; i++) cin>>gates_position[i];
    for(int i=STARTING_POS; i<=NGATES; i++) cin>>waiting[i];

    cout << find_min_distance_for_fisherment(n_fishing_spot, gates_position, waiting) << endl;
    return 0;
}


int find_min_distance_for_fisherment(const int n_fishing_spot, const vector<int>& gates_position, const vector<int>& waiting){
    vector<int> total_distance_for_gate(NGATES+STARTING_POS, INT_MAX), pos_start(4, INT_MAX);

    // Initialize
    int cumVal = 0;
    for(int i=3; i>=1; i--) {
        cumVal += waiting[i];
        pos_start[i] = n_fishing_spot - cumVal + 1;
    }

    while(pos_start[1]>=1){
        for(int i=NGATES; i>=STARTING_POS; i--){
            int curr_min_distance_for_gate;    

            if(pos_start[i]+waiting[i]-1<gates_position[i]) {
                int max_distance = gates_position[i] - pos_start[i] + 1;
                int min_distance = gates_position[i] - (pos_start[i] + waiting[i]) + 1;

                curr_min_distance_for_gate = (max_distance*(max_distance+1))/2 - (min_distance*(min_distance+1))/2;
            }
            else if(pos_start[i]>=gates_position[i]) {
                int min_distance = pos_start[i] - gates_position[i] ;
                int max_distance = (pos_start[i] + waiting[i]) - gates_position[i];

                curr_min_distance_for_gate = (max_distance*(max_distance+1))/2 - (min_distance*(min_distance+1))/2;
            }else {
                int leftDistance = gates_position[i] - pos_start[i] + 1;
                int rightDistance = (pos_start[i]+waiting[i]) - gates_position[i];
                curr_min_distance_for_gate = (leftDistance*(leftDistance+1))/2 + (rightDistance*(rightDistance+1))/2 - 1;
            }

            if(curr_min_distance_for_gate<total_distance_for_gate[i]){
                total_distance_for_gate[i] = curr_min_distance_for_gate;
                for(int j=i-1; j>=1; j--) total_distance_for_gate[j] = INT_MAX;
            }
        }

        // cout << "Debug "<<endl;
        // cout<< "Gate Positions: ";
        // for(int i=1; i<=3; i++) cout<<gates_position[i]<<" ";
        // cout<<endl;
        // cout<< "Starting Positions: ";
        // for(int i=1; i<=3; i++) cout<<pos_start[i]<<" ";
        // cout<<endl;
        // cout<< "Total Distance: ";
        // for(int i=1; i<=3; i++) cout<<total_distance_for_gate[i]<<" ";
        // cout<<endl;

        for(int j=1; j<=3; j++) pos_start[j]--;
    }

    return total_distance_for_gate[1] + total_distance_for_gate[2] + total_distance_for_gate[3];
}