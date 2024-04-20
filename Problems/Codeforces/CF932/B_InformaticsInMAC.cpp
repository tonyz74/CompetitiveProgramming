#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>

using namespace std;

void solve() {
    int n; cin >> n;
    map<int, int> mp;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
        mp[v[i]]++;
    }

    if (mp[0] == 0) {
        printf("%d\n", n);
        for (int i = 1; i <= n; i++) {
            printf("%d %d\n", i, i);
        }
        return;
    }

    if (mp[0] == 1) {
        printf("-1\n");
        return;
    }

    set<int> unused_a;
    set<int> unused_b;

    for (int i = 0; i <= n; i++) {
        unused_a.insert(i);
        unused_b.insert(i);
    }

    auto mex = [&] (const set<int>& ms) {
        assert(!ms.empty());
        return *ms.begin();
    };

    vector<int> b_mex(n + 1);
    for (int i = n; i >= 1; i--) {
        unused_b.erase(v[i]);
        b_mex[i] = mex(unused_b);
    }

    for (int i = 1; i < n; i++) {
        unused_a.erase(v[i]);
        if (mex(unused_a) == b_mex[i + 1]) {
            printf("2\n");
            printf("%d %d\n", 1, i);
            printf("%d %d\n", i + 1, n);
            return;
        }
    }

    printf("-1\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}