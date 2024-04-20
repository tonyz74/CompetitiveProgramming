#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;
const i64 MOD = 1e9 + 7;

void solve() {
    i64 n, k; cin >> n >> k;

    i64 all_sum = 0;
    bool any_gt_zero = false;
    vector<i64> a(n + 1);
    for (i64 i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > 0) any_gt_zero = true;
        all_sum += a[i];
    }

    if (!any_gt_zero) {
        cout << (((all_sum % MOD) + MOD) % MOD) << endl;
        return;
    }

    vector<i64> pfx(n + 1);
    // max sum that ends at n
    vector<i64> max_sum_subarray(n + 1);
    i64 best_idx = 0;

    i64 best_sum = 0;
    for (i64 i = 1; i <= n; i++) {
        pfx[i] = pfx[i - 1] + a[i];

        if (pfx[i] < pfx[best_idx]) {
            best_idx = i;
        }

        max_sum_subarray[i] = pfx[i] - pfx[best_idx];
        best_sum = max(best_sum, max_sum_subarray[i]);
    }

    i64 ans = 0;
    for (i64 i = 1; i <= k; i++) {
        ans += best_sum;
        best_sum *= 2;
        best_sum %= MOD;
        ans %= MOD;
    }

    cout << ((ans + all_sum) % MOD + MOD) % MOD << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}