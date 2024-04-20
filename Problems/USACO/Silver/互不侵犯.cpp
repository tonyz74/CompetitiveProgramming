#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

using i64 = long long;
i64 dp[2][10][102][(1 << 11)];

i64 set_to(i64 mask, i64 bit, int val) {
    if (val) {
        return mask | (1 << bit);
    } else {
        return mask & (~(1 << bit));
    }
}

i64 solve(i64 n, i64 max_k) {
    dp[0][0][0][0] = 1;
    dp[0][0][1][1 << n] = 1;

    // 0 1 0 0 0 0 0 0 0 0 0
    //   1 0 0 0 0 0 0 0 0 0
    //   ^

    for (i64 i = 0; i < n; i++) {
        i64 now = i % 2;
        i64 nxt = (i + 1) % 2;
        memset(dp[nxt], 0, sizeof(dp[nxt]));

        for (i64 j = 0; j < n; j++) {

            for (i64 k = 0; k <= max_k; k++) for (i64 mask = 0; mask < (1 << (n + 1)); mask++) {
                bool can_put_one = false;
                // printf("%lld, %lld, %lld, %s, => %lld\n", i, j, k, bitset<8>(mask).to_string().c_str(), dp[i][j][k][mask]);

                if (j != n - 1) {
                    int me = mask & (1 << n);
                    int top = mask & (1 << j);
                    int right = mask & (1 << (j + 1));
                    int right_two = (j + 2) >= n ? 0 : (mask & (1 << (j + 2)));
                    if (!me && !top && !right && !right_two) {
                        can_put_one = true;
                    }
                } else {
                    int above = mask & (1 << 0);
                    int right = mask & (1 << 1);
                    if (!above && !right) {
                        can_put_one = true;
                    }
                }

                i64 new_mask = set_to(mask, j, mask & (1 << n));
                i64 one_mask = set_to(new_mask, n, 1);
                i64 zero_mask = set_to(new_mask, n, 0);

                if (can_put_one) {
                    if (j == n - 1) {
                        dp[nxt][0][k + 1][one_mask] += dp[now][j][k][mask];
                    } else {
                        dp[now][j + 1][k + 1][one_mask] += dp[now][j][k][mask];
                    }
                }

                if (j == n - 1) {
                    dp[nxt][0][k][zero_mask] += dp[now][j][k][mask];
                } else {
                    dp[now][j + 1][k][zero_mask] += dp[now][j][k][mask];
                }
            }
        }
    }

    i64 res = 0;
    for (i64 mask = 0; mask < (1 << (n + 1)); mask++) {
        res += dp[(n - 1) % 2][n - 1][max_k][mask];
    }

    return res;
}

int main(void) {
    i64 n; i64 k; cin >> n >> k;
    cout << solve(n, k) << endl;
}