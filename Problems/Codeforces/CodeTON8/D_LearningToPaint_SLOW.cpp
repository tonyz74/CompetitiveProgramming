#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using i64 = long long;
using gt_set = multiset<i64, greater<i64> >;

void limited_insert(gt_set& s, i64 ins, i64 limit) {
    s.insert(ins);
    if ((i64) s.size() > limit) {
        s.erase(s.find(*s.rbegin()));
    }
}

void solve() {
    i64 N, K; cin >> N >> K;
    vector<vector<i64> > A(N + 1, vector<i64>(N + 1, 1e9));

    for (i64 i = 1; i <= N; i++) {
        for (i64 j = i; j <= N; j++) {
            cin >> A[i][j];
        }
    }

    vector<gt_set> dp(N + 1);
    vector<gt_set> prefix_best(N + 1);
    prefix_best[0] = gt_set{0};

    for (i64 i = 1; i <= N; i++) {
        gt_set best_now;
        // must be at least gap of 1, j + 2 is where i ends
        for (i64 j = 0; j <= i - 2; j++) {
            i64 add = A[j + 2][i];

            for (i64 x: prefix_best[j]) {
                limited_insert(best_now, x + add, K);
            }
        }

        // one exceptional case, pick all
        limited_insert(best_now, A[1][i], K);

        dp[i] = best_now;

        gt_set pfx_now = best_now;
        for (i64 x: prefix_best[i - 1]) {
            limited_insert(pfx_now, x, K);
        }
        prefix_best[i] = pfx_now;
    }

    for (i64 x: prefix_best[N]) {
        printf("%lld ", x);
    }
    printf("\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}