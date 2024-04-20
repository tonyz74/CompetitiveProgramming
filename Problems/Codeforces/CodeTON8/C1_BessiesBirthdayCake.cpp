#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;
using i64 = long long;

void solve() {
    i64 n, x, y; cin >> n >> x >> y;
    vector<i64> points(x + 1);
    for (i64 i = 1; i <= x; i++) cin >> points[i];
    std::sort(points.begin() + 1, points.end());

    i64 ans = x - 2;
    for (i64 i = 1; i <= x; i++) {
        i64 j = i + 1;
        if (j == x + 1) j = 1;

        i64 pi = points[i];
        i64 pj = points[j];

        if (pj > pi && pj == pi + 2) {
            ans++;
        }

        if (pj < pi) {
            if (n - pi + pj == 2) {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}