#include <iostream>
#include <vector>
#include <unordered_map>

using i64 = long long;
const i64 MOD = 1e9 + 7;

i64 dp[16][16][16][16][16][6];

// DFS -- current state is:
// have a colors with only 1 left, b with only 2 left, ...
// and I just placed skip + 1, so i cannot choose one from the colors with `skip` left
// return value => how many ways to place the remaining subsequence after picking this

i64 dfs(i64 a, i64 b, i64 c, i64 d, i64 e, i64 skip) {
    if (dp[a][b][c][d][e][skip] != -1) return dp[a][b][c][d][e][skip];

    // when to return 1? the remaining ways of placing the remaining...
    // if there's only 1 way to put the last thing (its all 0) return 1
    if (a + b + c + d + e == 0) return 1;

    long long now = 0;
    if (a > 0) now += (a - (skip == 1)) * dfs(a - 1, b, c, d, e, 0);
    if (b > 0) now += (b - (skip == 2)) * dfs(a + 1, b - 1, c, d, e, 1);
    if (c > 0) now += (c - (skip == 3)) * dfs(a, b + 1, c - 1, d, e, 2);
    if (d > 0) now += (d - (skip == 4)) * dfs(a, b, c + 1, d - 1, e, 3);
    if (e > 0) now += (e - (skip == 5)) * dfs(a, b, c, d + 1, e - 1, 4);

    return (dp[a][b][c][d][e][skip] = now % MOD);
}

using namespace std;

int main(void) {
    for (i64 a = 0; a <= 15; a++) {
        for (i64 b = 0; b <= 15; b++) {
            for (i64 c = 0; c <= 15; c++) {
                for (i64 d = 0; d <= 15; d++) {
                    for (i64 e = 0; e <= 15; e++) {
                        for (i64 s = 0; s <= 5; s++) {
                            dp[a][b][c][d][e][s] = -1;
                        }
                    }
                }
            }
        }
    }

    i64 k; cin >> k;
    vector<i64> x(6, 0);
    vector<i64> c(k + 1, 0);

    for (i64 i = 1; i <= k; i++) {
        cin >> c[i];
        x[c[i]]++;
    }

    cout << dfs(x[1], x[2], x[3], x[4], x[5], 0) << endl;
}