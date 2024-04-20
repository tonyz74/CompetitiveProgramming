#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using i64 = long long;

void solve() {
    i64 n, c; cin >> n >> c;
    vector<i64> a(n + 1);
    vector<pair<i64, i64> > v(n + 1);
    for (i64 i = 1; i <= n; i++) {
        cin >> a[i];
        v[i].first = a[i] - i * c;
        v[i].second = i;
    }

    // skip i = 1
    std::sort(v.begin() + 2, v.end());
    std::reverse(v.begin() + 2, v.end());

    i64 current_size = a[1];

    for (i64 i = 2; i <= n; i++) {
        i64 s = -v[i].first;

        if (s > current_size) {
            printf("NO\n");
            return;
        }

        current_size += a[v[i].second];
    }

    printf("YES\n");
}

int main(void) {
    i64 t; cin >> t;
    while (t--) solve();
}
