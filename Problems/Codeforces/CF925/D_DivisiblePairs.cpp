#include <iostream>
#include <map>
#include <vector>

using namespace std;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long ans = 0;
    map<pair<int, int>, int> mp;
    for (int i = n; i >= 1; i--) {
        ans += (long long) (mp[make_pair((x - a[i] % x) % x, a[i] % y)]);
        mp[make_pair(a[i] % x, a[i] % y)]++;
    }
    printf("%lld\n", ans);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}