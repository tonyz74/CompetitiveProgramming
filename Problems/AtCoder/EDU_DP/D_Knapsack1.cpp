#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

// j units of space left in knapsack
i64 dp[107][(int) 1e5 + 7];

int main(void) {
    i64 N, W; cin >> N >> W;  
    vector<i64> w(N + 1);
    vector<i64> v(N + 1);

    for (i64 i = 1; i <= N; i++) {
        cin >> w[i] >> v[i];
    }

    for (i64 i = 1; i <= N; i++) {
        for (i64 j = 1; j <= W; j++) {
            if (j - w[i] >= 0) {
                dp[i][j - w[i]] = max(dp[i][j - w[i]], dp[i - 1][j] + v[i]);
            }

            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    }

    i64 best = 0;
    for (i64 j = 0; j <= W; j++) {
        best = max(best, dp[N][j]);
    }
    cout << best << endl;
}