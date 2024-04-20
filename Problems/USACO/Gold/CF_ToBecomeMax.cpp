#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

i64 n, k;
vector<i64> a;

i64 get_cost(i64 pos, i64 val) {
    if (a[pos] >= val) return 0;
    if (pos == n) return 1e10;

    return (val - a[pos]) + get_cost(pos + 1, val - 1);
}

bool check(i64 max_wanted) {
    for (i64 i = 1; i <= n; i++) {
        // find cost needed to make a[i]
        i64 min_cost = get_cost(i, max_wanted);
        // printf("min cost to get a[%lld] = %lld to %lld is: %lld\n", i, a[i], max_wanted, min_cost);
        if (min_cost <= k) return true;
    }

    return false;
}

void solve() {
    cin >> n >> k;
    a.clear(); a.resize(n + 1);
    for (i64 i = 1; i <= n; i++) cin >> a[i];

    i64 lo = 1;
    i64 hi = 1e9;

    // find last true
    while (lo < hi) {
        i64 mid = (lo + hi + 1) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    if (lo == 1e9) {
        printf("%d\n", -1);
    } else {
        printf("%lld\n", lo);
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}