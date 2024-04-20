#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;
using i64 = long long;

#define MEX(not_in) (*(not_in).begin())

void solve() {
    i64 n; cin >> n;
    vector<i64> p(n + 1);
    vector<i64> pos_of(n + 2, -1);
    for (i64 i = 1; i <= n; i++) {
        cin >> p[i];
        pos_of[p[i]] = i;
    }

    set<i64> not_in_state;
    for (int i = 0; i <= n; i++) {
        not_in_state.insert(i);
    }
    not_in_state.erase(0);

    i64 L = pos_of[0], R = pos_of[0];
    i64 ans = 0;

    while (true) {
        // find all solutions with this current mex
        i64 mex_now = MEX(not_in_state);
        // printf("\nMEX: %lld\n", mex_now);

        i64 max_len = 2 * mex_now;
        i64 pos_next = pos_of[mex_now];

        // have already picked everything, just break (we only have 0..n-1)
        if (MEX(not_in_state) == n) {
            // final state: self
            ans++;
            break;
        }

        // transition to the next one
        while (pos_next < L) {
            i64 len_now = R - L + 1;
            if (len_now <= max_len) {
                i64 furthest_right = min(L + max_len - 1, n);
                ans += furthest_right - R + 1;
            }

            L--;
            not_in_state.erase(p[L]);
        }

        while (pos_next > R) {
            i64 len_now = R - L + 1;
            if (len_now <= max_len) {
                i64 furthest_left = max(R - (max_len - 1), 1ll);
                ans += L - furthest_left + 1;
            }

            R++;
            not_in_state.erase(p[R]);
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}