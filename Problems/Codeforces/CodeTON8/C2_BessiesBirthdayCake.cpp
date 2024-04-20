#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;
using i64 = long long;

void solve() {
    i64 n, x, y; cin >> n >> x >> y;
    vector<i64> points(x + 1);
    for (i64 i = 1; i <= x; i++) cin >> points[i];
    std::sort(points.begin() + 1, points.end());

    vector<i64> even_gaps;
    vector<i64> odd_gaps;

    i64 ans = x - 2;
    for (i64 i = 1; i <= x; i++) {
        i64 j = i + 1;
        if (j == x + 1) j = 1;

        i64 pi = points[i];
        i64 pj = points[j];

        i64 diff = 0;

        if (pj > pi) {
            diff = pj - pi;
        } else {
            diff = n - pi + pj;
        }

        if (diff == 2) {
            ans++;
        } else if (diff >= 3) {
            if (diff % 2 == 0) {
                even_gaps.push_back(diff);
            } else {
                odd_gaps.push_back(diff);
            }
        }
    }

    std::sort(even_gaps.begin(), even_gaps.end());
    std::sort(odd_gaps.begin(), odd_gaps.end());

    // start from small
    for (i64 i = 0; y > 0 && i < (int) even_gaps.size(); i++) {
        i64 to_full = (even_gaps[i] - 2) / 2;
        if (y < to_full) {
            ans += y * 2;
            y = 0;
        } else {
            ans += (to_full - 1) * 2;
            ans += 3;
            y -= to_full;
        }
    }

    for (i64 i = 0; y > 0 && i < (int) odd_gaps.size(); i++) {
        i64 used = min(y, (odd_gaps[i] - 1) / 2);
        y -= used;
        ans += used * 2;
    }

    // if (ans > n - 2) {
    //     printf("%lld\n", ans);
    // }
    assert(ans <= n - 2);
    cout << ans << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}