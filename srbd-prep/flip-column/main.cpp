#include<bits/stdc++.h>
using namespace std;

int main(){
    int nrow, ncol, k;
    cin>>nrow>>ncol>>k;

    unordered_map<string, int> patterns;
    //vector<vector<int>> graph (nrow, vector<int> (ncol));
    for(int i=0; i<nrow; i++){
        string pattern;
        for(int j=0; j<ncol; j++){
            char value;
            cin>>value;
            pattern.push_back(value);
        }
        patterns[pattern]++;
    }

    vector<pair<string, int>> sorted_patterns(patterns.begin(), patterns.end());

    sort(sorted_patterns.begin(), sorted_patterns.end(), [](const pair<string, int>& A, const pair<string, int>& B){
        //count 1 bit
        return A.second > B.second;
    });

    for(const auto& entry: sorted_patterns){
        int bit_flip_needed = 0;
        for(int i=0; i<entry.first.size(); i++){
            if(entry.first[i]=='0') bit_flip_needed+=1;
        }

        if(k%bit_flip_needed==0) {
            cout<<entry.second<<endl;
            return 0;
        }
    }

    cout<<"1"<<endl; // default case

    return 0;
}