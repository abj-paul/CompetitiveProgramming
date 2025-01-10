#include<iostream>
#include<climits>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

int main(){
    int n,m,K, input;
    cin>>n>>m>>K;

    unordered_map<string,int> patterns;

    for(int i=0; i<n; i++){
        string temp = "";
        for(int j=0; j<m; j++) {
            cin>>input;
            temp += char(48+input);
        }
        patterns[temp]++;
    }

    vector<pair<string,int>> sorted_patterns (patterns.begin(), patterns.end());
    sort(sorted_patterns.begin(), sorted_patterns.end(), [](const pair<string,int>& A, const pair<string,int>& B){
        return A.second > B.second;
    });

    //for(int i=0; i<sorted_patterns.size(); i++) cout<<sorted_patterns[i].first<<" --> "<<sorted_patterns[i].second<<endl;    
    for(int i=0; i<sorted_patterns.size(); i++){
        int countZero = 0;
        for(int j=0; j<sorted_patterns[i].first.size(); j++){
            if(sorted_patterns[i].first[j]=='0') countZero++;
        }    
        //cout << sorted_patterns[i].first << " with zeroes "<<countZero<<endl;
        if(countZero<=K && K % countZero == 0) {
            cout << sorted_patterns[i].second << endl;
            return 0;
        }
    }
    return 0;
}