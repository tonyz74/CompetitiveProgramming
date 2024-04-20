#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

// minimum weight to get a price of j
i64 dp[105][100007];

int main(void) {
    i64 N, W;
    cin >> N >> W;
    vector<i64> w(N + 1);
    vector<i64> v(N + 1);

    for (i64 i = 0; i <= N; i++) {
        for (i64 j = 0; j <= (i64) (1e5); j++) {
            dp[i][j] = 1e18;
        }
    }
    dp[0][0] = 0;

    for (i64 i = 1; i <= N; i++) {
        cin >> w[i] >> v[i];
    }

    for (i64 i = 1; i <= N; i++) {
        for (i64 j = 0; j <= (i64) 1e5; j++) {
            if (j >= v[i]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - v[i]] + w[i]);
            }
            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
        }
    }

    i64 best = 0;
    for (i64 value = 0; value <= (i64) (1e5); value++) {
        if (dp[N][value] <= W) {
            best = max(best, value);
        }
    }

    cout << best << endl;
}