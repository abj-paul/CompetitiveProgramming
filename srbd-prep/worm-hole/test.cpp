#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
struct point{
    int x,y;
};
struct hole{
    int x1,y1,x2,y2,value;
};
int mod(int a){
    if(a<=0)return -a;
    return a;
}
int cd(int a,int b,int c,int d){
    return mod(a-c)+mod(b-d);
}
hole a[50];

int n;
int ans=100000;
point source,destination;
int visited[20]={0};
void solve(int x,int y,int cost){
    ans=min(ans,cost + cd(x,y,destination.x,destination.y));
    for(int i=0;i<n;i++){
        if(!visited[i]){
            visited[i]=1;
            solve(a[i].x2,a[i].y2,cost+ cd(x,y,a[i].x1,a[i].y1) +a[i].value);
            solve(a[i].x1,a[i].y1,cost+ cd(x,y,a[i].x2,a[i].y2) +a[i].value);
            visited[i]=0;
        }
    }
}

int main() {
    
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
      cin>>n;
        cin>>source.x>>source.y>>destination.x>>destination.y;
        for(int i=0;i<n;i++){
            cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2>>a[i].value;
        }
        solve(source.x,source.y,0);
        cout<<ans<<endl;
        ans=100000;
    }
    return 0;
}
