#include<bits/stdc++.h>
using namespace std;

int n,m;
const int MAX_N = 1e5+1;
vector<int> adj[MAX_N];
int color[MAX_N] = {}, trace[MAX_N] = {};
int min_tmp = INT_MAX;
vector<int> tmp;

void dfs(int u){
	color[u] = 1;
	for (int v : adj[u]){
		if (color[v] == 0){
			trace[v] = u;
			dfs(v);
		}
		else if (color[v]==1){
			vector<int> ans;
			ans.push_back(u);
			int s = v;
			while(ans.back()!=v){
				s += ans.back();
				ans.push_back(trace[ans.back()]);
			}
			reverse(ans.begin(), ans.end());
			sort(ans.begin(), ans.end());
			if(s<min_tmp){
				min_tmp = s;
				tmp = ans;
			}
		}
	}
	color[u] = 0;
}

int main(){
	cin>>n>>m;
	for (int i = 0; i <= m; i++)
	{
		int u,v;
		cin>>u>>v;
		adj[u].push_back(v);
	}
	for(int i=1; i<=n; i++){
		if(color[i]==0){
			dfs(i);
		}
	}
	for(int x:tmp){
		cout<<x<<" ";
	}
	return 0;
}