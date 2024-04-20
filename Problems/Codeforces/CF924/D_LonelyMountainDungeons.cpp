#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

i64 get_pairs(i64 p, i64 g) {
    // p members, g groups
    i64 normal, extra;
    i64 g_normal, g_extra;
    normal = p / g;
    extra = (p % g == 0) ? (p / g) : (p / g + 1);
    g_extra = p % g;
    g_normal = g - g_extra;

    // these can have duplicates
    i64 nn_conns = normal * g_normal * (normal * (g_normal - 1)) / 2;
    // these can have duplicates
    i64 ee_conns = extra * g_extra * (extra * (g_extra - 1)) / 2;
    // these cannot, we're specifying "start at someone in a normal group"
    i64 en_conns = normal * g_normal * (extra * g_extra);

    return nn_conns + ee_conns + en_conns;
}

void solve() {
    i64 n, b, x; cin >> n >> b >> x;
    i64 mx = 0;
    vector<i64> c(n + 1);
    for (i64 i = 1; i <= n; i++) {
        cin >> c[i];
        mx = max(mx, c[i]);
    }

    vector<i64> pair_cnt(mx + 1, 0);
    vector<i64> capped_add(mx + 1, 0);
    for (i64 i = 1; i <= n; i++) {
        for (i64 k = 1; k <= c[i]; k++) {
            pair_cnt[k] += get_pairs(c[i], k);
        }
        capped_add[c[i]] += get_pairs(c[i], c[i]);
    }

    i64 ans = 0;
    i64 fixed_contrib = 0;
    for (i64 k = 1; k <= mx; k++) {
        i64 cmp = (fixed_contrib + pair_cnt[k]) * b - (k - 1) * x;
        // printf("[%lld] %lld %lld, cost: %lld, final: %lld\n", k, fixed_contrib, pair_cnt[k], (k - 1) * x, cmp);
        ans = max(ans, cmp);
        fixed_contrib += capped_add[k];
    }

    cout << ans << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve(); 
}