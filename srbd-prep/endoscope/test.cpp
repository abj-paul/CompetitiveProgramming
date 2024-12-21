#include <iostream>
using namespace std;
int grid[50][50];
int dir[][4]={{0,0,0,0},{-1,1,-1,1},{0,0,-1,1},{-1,1,0,0},{0,1,-1,0},{0,1,0,1},{-1,0,0,1},{-1,0,-1,0}};
int visited[50][50];
int dfsvisited[50][50];

void dfs(int m , int n , int i, int j, int &ans,int l){
    if(i<0 || i>=n || j<0 || j>=m){
        return;
    }
    if(grid[i][j]==0)return;
    if(dfsvisited[i][j])return;
    if(l<=0)return;
    if(!visited[i][j])ans++;
    
    visited[i][j]=1;
    dfsvisited[i][j]=1;
    
    int left = dir[grid[i][j]][0];
    int right = dir[grid[i][j]][1];
    int up = dir[grid[i][j]][2];
    int down = dir[grid[i][j]][3];
    
    if(j+left>=0 && j+left<m && dir[grid[i][j+left]][1]==1){    
        dfs(m,n,i,j+left,ans,l-1);
    }
    if(i+up>=0 && i+up<n && dir[grid[i+up][j]][3]==1){
        dfs(m,n,i+up,j,ans,l-1);
    }
    if(j+right>=0 && j+right<m && dir[grid[i][j+right]][0]==-1){
        dfs(m,n,i,j+right,ans,l-1);
    }
    if(i+down>=0 && i+down<n && dir[grid[i+down][j]][2]==-1){
        dfs(m,n,i+down,j,ans,l-1);
    }
    dfsvisited[i][j]=0;
    
}

int main() {
    int t;cin>>t;
    while(t--){
        int n,m,r,c,l;
        cin>>n>>m>>r>>c>>l;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>grid[i][j];
                visited[i][j]=0;
                dfsvisited[i][j]=0;
            }
        }
        int ans=0;
        dfs(m,n,r,c,ans,l);
        cout<<ans<<endl;
    }
    return 0;
}
