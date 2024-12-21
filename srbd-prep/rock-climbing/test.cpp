#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int n, m;

bool valid(int x, int y, vector<vector<int>> &a) {
    if (y < m && y >= 0 && a[x][y]>0) return true;
    return false;
}

void dfs(int x, int y, vector<vector<int>> &a, vector<vector<int>> &dp) {
    queue <pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        if (valid(x, y+1, a) && dp[x][y] < dp[x][y+1]) {
            dp[x][y+1] = dp[x][y];
            q.push({x, y+1});
        }
        if (valid(x, y-1, a) && dp[x][y] < dp[x][y-1]) {
            dp[x][y-1] = dp[x][y];
            q.push({x, y-1});
        }
        for (int r = 0; r < n; ++r) {
            if (r != x && a[r][y]>0) {
                int dis = max(abs(r - x), dp[x][y]);
                if (dis < dp[r][y]) {
                    dp[r][y] = dis;
                    q.push({r, y});
                }
            }
        }
    }
}

int main() {
    cin >> n >> m ;
    vector <vector<int>> a(n, vector <int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j] ;
        }
    }
    vector <vector<int>> dp(n, vector<int>(m, n-1));
    dp[n-1][0] = 0;
    dfs(n-1, 0, a, dp);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (3 == a[i][j]) cout << dp[i][j] << endl;
        }
    }
    return 0;
}