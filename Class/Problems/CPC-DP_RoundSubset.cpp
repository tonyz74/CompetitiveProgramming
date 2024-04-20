#include <iostream>
#include <vector>

// 2nd optimization: set values which were originally [0, 1] to a large
// range, this can reduce the dimensions in the DP

// originally it was DP[pos][n picked][n twos][n fives] = reachable or not,
// now it becomes DP[pos][n picked][n twos] = max n fives

using namespace std;

using i64 = long long;

struct factors {
    i64 n_2s = 0;
    i64 n_5s = 0;

    factors() {}

    factors(i64 x) {
        while (x % 2 == 0) {
            x /= 2;
            n_2s++;
        }

        while (x % 5 == 0) {
            x /= 5;
            n_5s++;
        }
    }
};

int main(void) {
    i64 N, K; cin >> N >> K;

    vector<factors> A(N + 1);
    for (i64 i = 1; i <= N; i++) {
        i64 V; cin >> V;
        A[i] = factors(V);
    }

    // DP[i][j] => i numbers picked so far, j 2s
    vector<vector<i64> > dp(K + 2, vector<i64>(3601, -1));
    dp[0][0] = 0;

    for (i64 pos = 1; pos <= N; pos++) {
        for (i64 n_picked = K; n_picked >= 0; n_picked--) {
            for (i64 num_twos = 3600; num_twos >= 0; num_twos--) {
                if (dp[n_picked][num_twos] == -1) continue;
                
                // use the current one
                i64 new_num_twos = min(num_twos + A[pos].n_2s, 3600ll);
                dp[n_picked + 1][new_num_twos] = max(
                    dp[n_picked + 1][new_num_twos],
                    dp[n_picked][num_twos] + A[pos].n_5s
                );

                // not using the current one has no effect
                // ...
            }
        }
    }

    i64 ans = 0;
    for (i64 num_twos = 0; num_twos <= 3600; num_twos++) {
        ans = max(ans, min(dp[K][num_twos], num_twos));
    }
    printf("%lld\n", ans);
}