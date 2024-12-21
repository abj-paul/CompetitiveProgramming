#include<bits/stdc++.h>
using namespace std;
#define endl "\n" 

int f(int i, int j,vector<int>& v,vector<vector<int>>& dp)
{
    if(i>j)return 0;

    int asn=INT_MIN;
    if(dp[i][j]!=-1)return dp[i][j];
    for(int ind=i;ind<=j;ind++)
    {
        int c;
        int n=v.size();
        if(((i-1) ==0) && ((j+1) == (n-1))) c=v[ind]+f(i,ind-1,v,dp)+f(ind+1,j,v,dp);//case when it is the only balloon left
        else  c=v[i-1]*v[j+1]+f(i,ind-1,v,dp)+f(ind+1,j,v,dp);//rest cases
        asn=max(asn,c);
    }
    return dp[i][j]=asn;
}

int main()
{
    long long n;
    cin>>n;
    vector<int> v;
    v.push_back(1);
    for (long long i = 0; i < n; i++)
    {
        long long p;cin>>p;
       v.push_back(p);

    }
        v.push_back(1);
    n=v.size();
    vector<vector<int>> dp(n+2,vector<int>(n+2,-1));

    cout<<f(1,n-2,v,dp)<<endl;
return 0;
}