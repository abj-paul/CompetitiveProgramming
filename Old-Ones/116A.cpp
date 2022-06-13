#include<iostream>
#include<vector>
using namespace std;

// Function Prototype
int solution(vector<pair<int,int>> record);

int main(){
    vector<pair<int,int>>record;
    int number_of_stops;
    int exit_count, enter_count;
    cin>>number_of_stops;
    for(int i=0; i<number_of_stops; i++){
        cin>>exit_count>>enter_count;
        record.push_back(make_pair(exit_count, enter_count));
     }

    cout<<solution(record)<<endl;
return 0;
}

int solution(vector<pair<int,int>> record){
    int current_capacity=0;
    int max_capacity=0;

    for(int i=0; i<record.size(); i++){
        current_capacity-=record[i].first;
        max_capacity=max(max_capacity, current_capacity);
        current_capacity+=record[i].second;
        max_capacity=max(max_capacity, current_capacity);
    }
    return max_capacity;
}
