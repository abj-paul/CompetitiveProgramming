#include<bits/stdc++.h>
using namespace std;

int max_ones_in_array(const vector<int>& bits) ;

int main(){
    int N;
    cin>>N;
    vector<int> bits(N);
    for(int i=0; i<N; i++) cin>>bits[i];

    cout << max_ones_in_array(bits) <<endl;

    return 0;
}

int max_ones_in_array(const vector<int>& bits) {
    int max_continuous_0s = INT_MIN;

    for(int i=0; i<bits.size(); i++){
        for(int j = i; j<bits.size(); j++){
            int continuous_0s=0;
            for(int k=i; k<=j; k++){
                if(bits[k]==0) continuous_0s++;
                else continuous_0s = 0;
                max_continuous_0s = max(max_continuous_0s, continuous_0s);
            }
        }
    }

    int total_1s=0, total_0s=0;
    for(int i=0; i<bits.size(); i++)
        if(bits[i]==1) total_1s++;
        else total_0s++;
        
    if(total_0s>total_1s+max_continuous_0s) return total_0s;

    return total_1s+max_continuous_0s;
}