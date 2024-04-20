#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define LEFT -1
#define RIGHT 1

using i64 = long long;

void solve() {
    int N; cin >> N;
    string S; cin >> S;
    S = "." + S;

    vector<i64> Ls(1);
    vector<i64> Rs(1);

    for (int start = 1; start <= N; start++) {
        if (S[start] == '>') Rs.push_back(start);
        if (S[start] == '<') Ls.push_back(start);
    }

    vector<i64> pfx_L(Ls.size());
    vector<i64> pfx_R(Rs.size());

    for (i64 i = 1; i < (i64) Ls.size(); i++) {
        pfx_L[i] = pfx_L[i - 1] + Ls[i];
    }
    for (i64 i = 1; i < (i64) Rs.size(); i++) {
        pfx_R[i] = pfx_R[i - 1] + Rs[i];
    }


    for (int start = 1; start <= N; start++) {
        // find first in L that is greater than or equal to start
        i64 found_L = std::lower_bound(Ls.begin() + 1, Ls.end(), start) - Ls.begin();
        // first in R that is strictly greater than start
        i64 found_R = std::upper_bound(Rs.begin() + 1, Rs.end(), start) - Rs.begin() - 1;

        // i'm too large for everything in Ls, no L after me
        if (found_L == (i64) Ls.size()) {
            printf("%lld ", (i64) ((N + 1) - start));
            continue;
        }
        // even the first R was greater than me, no R before me 
        else if (found_R == -1) {
            printf("%lld ", (i64) start);
            continue;
        }

        i64 n_L_above = Ls.size() - found_L;
        i64 n_R_below = found_R;

        i64 L_offset = found_L - 1;
        i64 R_offset = found_R + 1;

        i64 min_len = min(n_L_above, n_R_below);

        int dir = 0;
        // will exit at the right
        if (n_R_below > n_L_above || (n_R_below == n_L_above && S[start] == '<')) {
            dir = 1;
        } else {
            dir = -1;
        }

        // right
        if (dir == 1 && S[start] == '>') {
            i64 ans = (N + 1) - Rs[found_R];

            ans += 2 * (pfx_L[L_offset + min_len] - pfx_L[L_offset]);
            ans -= 2 * (pfx_R[R_offset - 2] - pfx_R[R_offset - (min_len + 1) - 1]);

            // for (i64 i = 1; i <= min_len; i++) {
            //     ans += 2 * L[i];
            // }

            // for (i64 i = 2; i <= min_len + 1; i++) {
            //     ans -= 2 * R[R_sz - i];
            // }

            cout << ans << " ";

        } else if (dir == 1 && S[start] == '<') {
            i64 ans = (N + 1) + Ls[found_L];

            ans += 2 * (pfx_L[L_offset + min_len] - pfx_L[L_offset + 2 - 1]);
            ans -= 2 * (pfx_R[R_offset - 1] - pfx_R[R_offset - min_len - 1]);

            // for (i64 i = 2; i <= min_len; i++) {
            //     ans += 2 * L[i];
            // }
            // for (i64 i = 1; i <= min_len; i++) {
            //     ans -= 2 * R[R_sz - i];
            // }

            cout << ans << " ";

        }

        // left 
        else if (dir == -1 && S[start] == '>') {
            i64 ans = -Rs[found_R];

            ans += 2 * (pfx_L[L_offset + min_len] - pfx_L[L_offset]);
            ans -= 2 * (pfx_R[R_offset - 2] - pfx_R[R_offset - (min_len) - 1]);

            // for (i64 i = 1; i <= min_len; i++) {
            //     ans += 2 * L[i]; 
            // }
            // for (i64 i = 2; i <= min_len; i++) {
            //     ans -= 2 * R[R_sz - i];
            // }

            cout << ans << " ";

        } else if (dir == -1 && S[start] == '<') {
            i64 ans = Ls[found_L];

            ans += 2 * (pfx_L[L_offset + min_len + 1] - pfx_L[L_offset + 2 - 1]);
            ans -= 2 * (pfx_R[R_offset - 1] - pfx_R[R_offset - min_len - 1]);

            // for (i64 i = 2; i <= min_len + 1; i++) {
            //     ans += 2 * L[i];
            // }
            // for (i64 i = 1; i <= min_len; i++) {
            //     ans -= 2 * R[R_sz - i];
            // }

            cout << ans << " ";
        }

    }
    printf("\n");
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}