#include <iostream>
#define size 15
using namespace std;


//0 nothing, 1 money, 2 enemy
int N, arr[size][size] = {};
int x_[] = {-1, -1, -1};
int y_[] = {-1, 0, 1};
int res;

void bombing(int arr[][size], int index) {
    for(int i = N - 1; i >= N - 5 && i >= 0; i--)
        for(int j = 0; j < 5; j++)
            if(arr[i][j] == 2) arr[i][j] = 0;
}
void backtrack(int arr[][size], int x, int y, int money, int bomb) {
    if(x == 0) {
        if(res < money) res = money;
        return;
    }
    for(int i = 0; i < 3; i++) {
        int xx = x + x_[i];
        int yy = y + y_[i];
        if(xx >= 0 && yy >= 0 && xx < N && yy < 5) {
            if(arr[xx][yy] == 0)
                backtrack(arr, xx, yy, money, bomb);
            else if(arr[xx][yy] == 1)
                backtrack(arr, xx, yy, money + 1, bomb);
            else if(arr[xx][yy] == 2) {
                if(bomb > 0) {
                    int arr_temp[size][size] = {};
                    for(int i = 0; i < x; i++)
                        for(int j = 0; j < 5; j++)
                            arr_temp[i][j] = arr[i][j];
                    bombing(arr_temp, x);
                    backtrack(arr_temp, xx, yy, money, bomb - 1);
                } else
                    if(res < money) res = money;
            }
        }

    }

}
int main() {
    freopen("input.txt", "r", stdin);
    int T; cin >> T;
    for(int tc = 1; tc <= T; tc++) {
        cin >> N;
        for(int i = 0; i < N; i++)
            for(int j = 0; j < 5; j++)
                cin >> arr[i][j];
        res = 0;
        backtrack(arr, N, 5/2, 0, 1);
        cout << "#" << tc << ' ' << res << endl;
    }
    return 0;
}