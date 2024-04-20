#include <iostream>
#include <vector>
#include <set>

using namespace std;
using i64 = long long;

void swap_vals(multiset<i64>& a, multiset<i64>& b, i64& sa, i64& sb, i64 va, i64 vb) {
    sa -= va;
    sa += vb;
    sb += va;
    sb -= vb;

    a.erase(a.find(va));
    a.insert(vb);
    b.erase(b.find(vb));
    b.insert(va);
}

void solve() {
    int n, m, k; cin >> n >> m >> k;

    multiset<i64> a;
    multiset<i64> b;

    i64 jelly_score = 0;
    i64 gelly_score = 0;

    for (int i = 1; i <= n; i++) {
        i64 x; cin >> x;
        jelly_score += x;
        a.insert(x);
    }

    for (int i = 1; i <= m; i++) {
        i64 x; cin >> x;
        gelly_score += x;
        b.insert(x);
    }

    // first two rounds, then optionally a 3rd round
    
    // round 1
    if (*a.begin() < *b.rbegin()) {
        swap_vals(a, b, jelly_score, gelly_score, *a.begin(), *b.rbegin());
    }

    if (k == 1) {
        printf("%lld\n", jelly_score);
        return;
    }

    // round 2
    if (*b.begin() < *a.rbegin()) {
        swap_vals(a, b, jelly_score, gelly_score, *a.rbegin(), *b.begin());
    }

    if (k % 2 == 0) {
        printf("%lld\n", jelly_score);
        return;
    }

    // round 3
    if (*a.begin() < *b.rbegin()) {
        swap_vals(a, b, jelly_score, gelly_score, *a.begin(), *b.rbegin());
    }
    printf("%lld\n", jelly_score);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}