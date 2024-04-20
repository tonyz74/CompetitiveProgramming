#include <iostream>
#include <vector>
#include <set>

using namespace std;
using i64 = long long;

void solve() {
    i64 n; cin >> n;
    vector<i64> a_orig(n + 1);
    vector<i64> b_orig(n + 1);

    for (i64 i = 1; i <= n; i++) {
        cin >> a_orig[i];
    }
    for (i64 i = 1; i <= n; i++) {
        cin >> b_orig[i];
    }

    if (n == 1) {
        printf("0\n");
        return;
    }

    multiset<i64> a;
    multiset<i64> b;
    multiset<pair<i64, i64> > bad;

    // initial setup: put in the first and the last
    a.insert(a_orig[1]); a.insert(a_orig[2]);
    b.insert(b_orig[1]); b.insert(b_orig[2]);
    bad.insert(make_pair(b_orig[1], -1e10));            // first
    bad.insert(make_pair(1e10, a_orig[2]));             // last
    if (b_orig[2] > a_orig[1]) {
        bad.insert(make_pair(b_orig[2], a_orig[1]));
    }

    for (i64 i = 3; i <= n; i++) {
        // try to insert a_orig[i], b_orig[i]
        auto insert_a_before = a.upper_bound(a_orig[i]);
        auto insert_b_before = b.lower_bound(b_orig[i]);

        auto lb = bad.lower_bound(make_pair(b_orig[i], -1e11));
        // the A it's connected to
        while (lb->second <= a_orig[i]) {
            lb = bad.erase(lb);
        }

        // insert possible new bad pairings
        // if the new b is bad, they must've been previously within bad
        // new a must not be bad
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}