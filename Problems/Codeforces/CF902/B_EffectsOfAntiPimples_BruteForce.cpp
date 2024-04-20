#include <iostream>

using namespace std;
using i64 = long long;

const i64 MOD = 998244353;

int main(void) {
    i64 n; cin >> n;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    i64 ans = 0;

    for (int mask = 1; mask <= (1 << n) - 1; mask++) {
        vector<int> idx;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                idx.push_back(i + 1);
            }
        }

        i64 mx = 0;
        for (int i = 1; i <= n; i++) {
            for (int j: idx) {
                if (i % j == 0) {
                    mx = max(mx, a[i]);
                }
            }
        }

        ans += mx;
        ans %= MOD;
    }

    cout << ans << endl;
}