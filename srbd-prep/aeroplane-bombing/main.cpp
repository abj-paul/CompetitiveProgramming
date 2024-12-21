#include <bits/stdc++.h>
using namespace std;

// Global variables
int grid[15][5];
int n;

// Function prototype
int simulate_game(int x, int y, bool check, int index);

int main() {
    int t;
    cin >> t;

    int test_case = 1; // To correctly track test case numbers
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> grid[i][j];
            }
        }

        // Start from the bottom row (n-1), middle column (2)
        int coins = simulate_game(n - 1, 2, false, 0);
        cout << "#" << test_case << " " << coins << endl;
        test_case++;
    }

    return 0;
}

int simulate_game(int x, int y, bool check, int index) {
    // Base case: if out of bounds or invalid state
    if (x < 0 || y < 0 || y >= 5 || (grid[x][y] == 2 && index >= 5)) {
        return 0;
    }

    int ans = INT_MIN;
    int next[3][2] = {
        {-1, -1}, // Move to top-left
        {-1, 0},  // Move straight up
        {-1, 1}   // Move to top-right
    };

    for (int i = 0; i < 3; i++) {
        int dx = x + next[i][0];
        int dy = y + next[i][1];
        int p = 0;

        // Ensure within bounds before recursive call
        if (dx >= 0 && dx < n && dy >= 0 && dy < 5) {
            if (grid[dx][dy] == 1 && !check) {
                // Collect a coin when check is false
                p = 1 + simulate_game(dx, dy, false, index);
            } else if (grid[dx][dy] == 1 && check) {
                // Collect a coin when check is true and increment index
                p = 1 + simulate_game(dx, dy, true, index + 1);
            } else if (grid[dx][dy] == 2) {
                // Pass through a "2" cell and set check to true
                p = simulate_game(dx, dy, true, index + 1);
            } else if (grid[dx][dy] == 0) {
                // Pass through a "0" cell without collecting coins
                p = simulate_game(dx, dy, check, index + (check ? 1 : 0));
            }
        }

        // Maximize result
        ans = max(ans, p);
    }

    return ans;
}
