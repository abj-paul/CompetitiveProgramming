#include <iostream>
#include <climits>
#include <vector>
using namespace std;

const int NGATES = 3, STARTING_INDEX=1;
int find_min_traversal_distance(int num_of_fishing_spots, const vector<int>& gate_position, const vector<int>& waiting);

int main(){
    int num_of_fishing_spots;
    cin>>num_of_fishing_spots;

    vector<int> gate_position (NGATES + STARTING_INDEX), waiting(NGATES+STARTING_INDEX);

    for(int i=1; i<=NGATES; i++) cin>>gate_position[i];
    for(int i=1; i<=NGATES; i++) cin>>waiting[i];

    cout << find_min_traversal_distance(num_of_fishing_spots, gate_position, waiting) <<endl;

    return 0;
}


int find_min_traversal_distance(int num_of_fishing_spots, const vector<int>& gate_position, const vector<int>& waiting){
    int suffix_sum = 0;
    vector<int> starting_position (NGATES+STARTING_INDEX);
    int ans = INT_MAX;

    for(int i=NGATES; i>=STARTING_INDEX; i--){ // initialize by assigning all to right
        suffix_sum += waiting[i];
        starting_position[i] = num_of_fishing_spots - suffix_sum + 1;
    }

    vector<int> distance (NGATES + STARTING_INDEX, INT_MAX);
    while(starting_position[1]>=STARTING_INDEX){
        for(int i=NGATES; i>=STARTING_INDEX; i--){
            int total_distance;
            if(starting_position[i] + waiting[i] - 1 < gate_position[i]){ //all fishermen in left of gate 
                int min_distance = gate_position[i] - (starting_position[i]+waiting[i]-1); // why not +1
                int max_distance = gate_position[i] - starting_position[i] + 1;
                total_distance = (max_distance*(max_distance+1))/2 - (min_distance*(min_distance+1))/2 ;
            }
            else if(starting_position[i] >= gate_position[i]){ // right side , OK
                int min_distance = starting_position[i]-gate_position[i]; //why not +1, we consider it in max  (once)
                int max_distance = (starting_position[i]+waiting[i]) - gate_position[i];
                total_distance = (max_distance*(max_distance+1))/2 - (min_distance*(min_distance+1))/2 ;
            }else {
                int leftMaxDistance = gate_position[i] - starting_position[i] + 1;
                int rightMaxDistance = (starting_position[i]+waiting[i]) - gate_position[i];

                total_distance = (leftMaxDistance*(leftMaxDistance+1))/2 + (rightMaxDistance*(rightMaxDistance+1))/2 - 1; // gate position itself gets double-counted so we -1
            }
            if(total_distance<distance[i]) {
                distance[i] = total_distance;
                distance[i-1] = INT_MAX;
            }
        }

        ans = min(ans, distance[1]+distance[2]+distance[3]);


        // Debug
        // cout<<"Gates: ";
        for(int i=0; i<=gate_position.size(); i++) cout << gate_position[i]<<" ";
        cout<<endl;
        cout<<"Starting position: ";
        for(int i=0; i<=starting_position.size(); i++) cout << starting_position[i]<<" ";
        cout<<endl;
        cout<<"Total Distance: ";
        for(int i=0; i<=distance.size(); i++) cout << distance[i]<<" ";
        cout<<endl;
        cout<<"Total Minimum Distance = "<<ans<<endl;
        
        // Shift Left
        for(int i=STARTING_INDEX; i<=NGATES; i++) starting_position[i]--;
    }
    return ans;
}