#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

void solve() {
    i64 N, K; cin >> N >> K;
    vector<i64> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    vector<vector<i64> > dp(N + 1, vector<i64>(K + 1, 1e18));

    vector<i64> pfx(N + 1, 0);
    for (i64 i = 1; i <= N; i++) {
        pfx[i] = pfx[i - 1] + A[i];
    }

    // for (i64 i = 1; i <= N; i++) {
    //     dp[i][0] = pfx[i];
    //     printf("%lld %lld\n", i, pfx[i]);
    // }

    for (i64 i = 1; i <= N; i++) {
        for (i64 prev_cost = 0; prev_cost <= min(K, i - 1); prev_cost++) {
            dp[i][prev_cost] = min(dp[i][prev_cost], dp[i - 1][prev_cost] + A[i]);

            i64 min_val = 1e18;
            i64 lhs = i;

            while (true) {
                min_val = min(min_val, A[lhs]);

                i64 range_size = i - lhs + 1;
                i64 cost = range_size - 1;

                if (cost + prev_cost > K) break;
                if (lhs <= 0) break;

                // take right up to lhs
                i64 value = range_size * min_val;
                if (lhs - 1 >= 1) value += dp[lhs - 1][prev_cost];

                // if (value == 11 && i == 5) {
                    // printf("hit the 11\n");
                    // printf("%lld %lld %lld %lld\n", range_size, lhs, prev_cost, cost);
                    // printf("%lld\n", dp[lhs - 1][prev_cost]);
                // }

                dp[i][prev_cost + cost] = min(dp[i][prev_cost + cost], value);

                lhs--;
            }
        }
    }

    // for (i64 i = 1; i <= N; i++) {
    //     printf("%lld: ", i);
    //     for (i64 k = 0; k <= K; k++) {
    //         printf("[%lld] => %lld, ", k, dp[i][k]);
    //     }
    //     cout << endl;
    // }

    i64 mn = 1e18;
    for (i64 k = 0; k <= K; k++) {
        mn = min(mn, dp[N][k]);
    }
    cout << mn << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
