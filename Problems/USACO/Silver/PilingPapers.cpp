#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

using i64 = long long;
const i64 mod = 1e9 + 7;

i64 fastpow(i64 x, i64 pow) {
    if (pow == 0) return 1;
    if (pow == 1) return x;

    i64 ans;
    if (pow % 2 == 0) {
        ans = fastpow(x * x, pow / 2);
    } else {
        ans = x * fastpow(x * x, (pow - 1) / 2);
    }
    ans %= mod;

    return ans;
}

i64 N;
i64 C[305][305];
i64 ans[305][305];

// DP[i][l][r][l_lt][r_lt]
// I've currently placed i papers.
// There are l papers on the left, starting from the front.
// There are r papers on the right, starting from the back.
// l_lt represents if the front part is less than vs equal to the max given.
// r_lt represents if the front part is less than vs greater than or equal to the max given.
// The value stored here represents the number of ways to construct something like this.
i64 dp[304][20][20][2][2];

i64 digits[305];

int str_rep[20];
i64 get_str_rep(i64 n) {
    memset(str_rep, 0, sizeof(str_rep));
    string S = to_string(n);
    for (int i = 1; i <= (int) S.size(); i++) {
        str_rep[i] = S[i - 1] - '0';
    }
    return S.length();
}

void solve(i64 max) {
    i64 n_digits = get_str_rep(max);

    // caculate all possibilities with n. digits that are
    // less than the maximum n digits, so we can just do
    // whatever we want.
    for (i64 i = 1; i <= N; i++) {
        for (i64 j = i; j <= N; j++) {
            for (i64 k = 0; k <= min(j - i + 1, n_digits - 1); k++) {
                (ans[i][j] += (C[j - i + 1][k] * fastpow(2, k) % mod) % mod) %= mod;
            }
        }
    }

    for (i64 j = 1; j <= N; j++) {
        memset(dp, 0, sizeof(dp));
        dp[j + 1][0][0][0][0] = 1;

        // We must go backwards!
        // Since we can insert all over the place (front vs back), we can never
        // be sure where a paper's final position is if we look front to back.
        //
        // However, if we're going backwards... for example, let's say we place the
        // last paper at the front. This will be the global front. Given this info,
        // we try also picking the second last to be the front. This will be one
        // to the right of our last paper.
        // 
        // We can do similar reasoning for adding things from the back.

        for (i64 i = j; i >= 1; i--) {
            int digit_to_add = digits[i];

            for (i64 l = 0; l <= n_digits; l++) {
                for (i64 r = 0; r <= n_digits - l; r++) {
                    for (int l_lt = 0; l_lt <= 1; l_lt++) {
                        for (int r_lt = 0; r_lt <= 1; r_lt++) {
                            // CURRENTLY, I AM AT THE POV OF:
                            // dp[i + 1][l][r][l_lt][r_lt].
                            // I am trying to transition others that I'm linked to.
                            i64 self = dp[i + 1][l][r][l_lt][r_lt];

                            // I don't do anything. Everything stays the same, i -= 1;
                            (dp[i][l][r][l_lt][r_lt] += self) %= mod;

                            // I add something to the front. The thing I add must be
                            // smaller or equal to the max value there if i'm not already
                            // considered smaller.
                            if (l_lt || digit_to_add <= str_rep[l + 1]) {
                                int new_l_lt = (l_lt) || (digit_to_add < str_rep[l + 1]);
                                (dp[i][l + 1][r][new_l_lt][r_lt] += self) %= mod;
                            }

                            int new_r_lt = -1;
                            int right_pos = n_digits - r;
                            if (str_rep[right_pos] > digit_to_add) {
                                new_r_lt = 0;
                            } else if (str_rep[right_pos] == digit_to_add) {
                                new_r_lt = r_lt;
                            } else {
                                new_r_lt = 1;
                            }
                            
                            (dp[i][l][r + 1][l_lt][new_r_lt] += self) %= mod;
                        }
                    }
                }
            }

            for (i64 i1 = 0; i1 <= n_digits; i1++) {
                i64 j1 = n_digits - i1;
                for (int l_lt = 0; l_lt <= 1; l_lt++) {
                    for (int r_lt = 0; r_lt <= 1; r_lt++) {
                        if (l_lt || !r_lt) {
                            ans[i][j] += dp[i][i1][j1][l_lt][r_lt];
                            ans[i][j] %= mod;
                        }
                    }
                }
            }
        }
    }
}

void pascals_triangle() {
    for (int i = 0; i < 305; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            C[i][j] %= mod;
        }
    }
}

int main(void) {
    pascals_triangle();
    i64 A, B; cin >> N >> A >> B;

    for (int i = 1; i <= N; i++) {
        cin >> digits[i];
    }

    solve(A - 1);

    for (int i = 0; i < 305; i++) {
        for (int j = 0; j < 305; j++) {
            ans[i][j] = -ans[i][j];
        }
    }
    solve(B);

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int L, R; cin >> L >> R;
        printf("%lld\n", ans[L][R]);
    }
}