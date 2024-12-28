#include<iostream>
#include<climits>
#include<vector>

using namespace std;

const int NGATES = 3;
const int UNVISITED = -1, VISITED = 1, EMPTY_SPOT=-1;

// Function Prototypes
int find_min_cost_to_move(int n, const vector<int>& gates, const vector<int>& nwaiting);
int generate_combinations(int orderIndex, vector<int>& gateOrder, vector<int>& visited, int N, const vector<int>& gates, const vector<int>& nwaiting);
int assign_optimum_fishing_spot(int orderIndex, const vector<int>& gateOrder, vector<int>& fishing_spot, int N, const vector<int>& gates, const vector<int>& nwaiting);



int main(){
    int n;
    cin>>n;

    vector<int> gates(NGATES+1), nwaiting(NGATES+1);
    for(int i=1; i<NGATES; i++) cin>>gates[i];
    for(int i=1; i<NGATES; i++) cin>>nwaiting[i];

    cout<<find_min_cost_to_move(n,gates,nwaiting)<<endl;
    return 0;
}

int generate_combinations(int orderIndex, vector<int>& gateOrder, vector<int>& visited, int N, const vector<int>& gates, const vector<int>& nwaiting){
    if(orderIndex>NGATES){
        vector<int> fishing_spot (N+1, EMPTY_SPOT); 
        return assign_optimum_fishing_spot(1, gateOrder, fishing_spot, N, gates, nwaiting);
    }

    int min_ans = INT_MAX;

    for(int i=1; i<=NGATES; i++){
        if(visited[i]==UNVISITED){
            gateOrder[orderIndex] = i;
            visited[i] = VISITED;
            min_ans = min(min_ans,generate_combinations(orderIndex+1, gateOrder, visited, N, gates, nwaiting));
            visited[i] = UNVISITED;
        }
    }
    return min_ans;
}

int find_min_cost_to_move(int n, const vector<int>& gates, const vector<int>& nwaiting){
    vector<int> gateOrder(NGATES+1), visited(NGATES+1, UNVISITED);

    return generate_combinations(1,gateOrder,visited, n, gates, nwaiting);
}

int assign_optimum_fishing_spot(int orderIndex, const vector<int>& gateOrder, vector<int>& fishing_spot, int N, const vector<int>& gates, const vector<int>& nwaiting){
    int ans = INT_MAX;
    int gateIndex = gateOrder[orderIndex];
    int gatePosition = gates[gateIndex];
    int nfishermen = nwaiting[gateIndex];

    int distance = 0;
    while(nfishermen>0){
        cout<<"Stuck in while loop with "<<nfishermen<<" fishermen and distance "<<distance<<endl;
        // Direct position
        if(fishing_spot[gatePosition]==EMPTY_SPOT){
            fishing_spot[gatePosition] = distance + 1;
            distance++;
            nfishermen--;
        }

        int left = gatePosition - distance;
        int right = gatePosition + distance;

        // Special case
        if(nfishermen==1 && fishing_spot[left]==EMPTY_SPOT && fishing_spot[right]==EMPTY_SPOT && left>=0 && right<=N){
            vector<int> temp_fs (fishing_spot.begin(), fishing_spot.end());
            temp_fs[left] = distance + 1;
            int leftAns = assign_optimum_fishing_spot(orderIndex+1, gateOrder, temp_fs, N, gates, nwaiting);
            fishing_spot[right] = distance + 1;
            int rightAns = assign_optimum_fishing_spot(orderIndex+1, gateOrder, fishing_spot, N, gates, nwaiting);
            
            nfishermen--;
            distance++;
            ans = min(ans, min(leftAns, rightAns));
        }
         

        // left-right

        if(left>=1 && fishing_spot[left] == EMPTY_SPOT){
            fishing_spot[left] = distance + 1;
            nfishermen--;
        }
        if(right<=N && fishing_spot[right] == EMPTY_SPOT){
            fishing_spot[right] = distance + 1;
            nfishermen--;
        }

        distance++;
    }

    if(orderIndex>NGATES){
        int distance = 0;
        for(int i=0; i<fishing_spot.size(); i++) distance += fishing_spot[i];
        return min(ans,distance);
    } else return assign_optimum_fishing_spot(orderIndex+1, gateOrder, fishing_spot, N, gates, nwaiting);

}