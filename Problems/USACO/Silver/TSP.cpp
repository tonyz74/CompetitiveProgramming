#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

i64 adj[16][16];
i64 dp[16][1 << 15];

int main(void) {
    i64 N; cin >> N;
    for (i64 i = 0; i < N; i++) {
        for (i64 j = 0; j < N; j++) {
            cin >> adj[i][j];
        }
    }

    for (i64 i = 0; i < 16; i++) {
        for (i64 mask = 0; mask < (1 << 15); mask++) {
            dp[i][mask] = 1e18;
        }
    }

    for (i64 i = 0; i < N; i++) {
        dp[i][0 | (1 << i)] = 0;
    }

    // mask in increasing order actually works:
    // states with more ones will always be greater than
    // the states they came from.

    for (i64 mask = 0; mask < (1 << N); mask++) {
        for (i64 i = 0; i < N; i++) {

            for (i64 j = 0; j < N; j++) {
                if (j == i) continue;

                if (adj[i][j] != -1 && (mask & (1 << j)) == 0) {
                    dp[j][mask | (1 << j)] = min(
                        dp[j][mask | (1 << j)],
                        dp[i][mask] + adj[i][j]
                    );
                }
            }

        } 
    }

    i64 ans = 1e18;
    for (i64 ep = 0; ep < N; ep++) {
        ans = min(ans, dp[ep][(1 << N) - 1]);
    }

    cout << ans << endl;
}