#include<iostream>
#include<climits>
#include<unordered_map>
#include<vector>
#include<algorithm>
using namespace std;

int get_max_similar_rows_after_toggle(int K, const vector<vector<int>>& grid);

int main(){
    int n,m, K;
    cin>>n>>m>>K;

    vector<vector<int>> grid (n, vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cin>>grid[i][j];
    }

    cout << get_max_similar_rows_after_toggle(K, grid) << endl;

    return 0;
}

int get_max_similar_rows_after_toggle(int K, const vector<vector<int>>& grid){
    unordered_map<string, int> patterns;
    int n=grid.size(), m = grid[0].size();

    for(int i=0; i<n; i++){
        string pattern = "";
        for(int j=0; j<m; j++) pattern += char(48+grid[i][j]);
        patterns[pattern]++;
    }

    vector<pair<string,int>> sorted_patterns (patterns.begin(), patterns.end());
    sort(sorted_patterns.begin(), sorted_patterns.end(), [](const pair<string,int>& A, const pair<string,int>& B){
        return A.second > B.second;
    });
    //for(int i=0; i<sorted_patterns.size(); i++) cout<<sorted_patterns[i].first << " = " << sorted_patterns[i].second << endl;

    for(int i=0; i<sorted_patterns.size(); i++){
        int zero_count = 0;
        for(int j=0; j<sorted_patterns[i].first.size(); j++){
            if(sorted_patterns[i].first[j]=='0') zero_count++;
        }
        if(zero_count<=K &&  K % zero_count == 0) return sorted_patterns[i].second;
    }
    return -1;
}