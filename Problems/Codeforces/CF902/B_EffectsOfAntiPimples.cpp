#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

const i64 MOD = 998244353;

int main(void) {
    i64 n; cin >> n;
    vector<i64> a(n + 1);
    vector<pair<i64, int> > max_with(n + 1);

    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 1; i <= n; i++) {
        i64 x = 0;
        for (int j = i; j <= n; j += i) {
            x = max(x, a[j]);
        }
        max_with[i] = make_pair(x, i);
    }

    std::sort(max_with.begin() + 1, max_with.end());

    i64 ans = 0;
    i64 pow2 = 1;

    for (int i = 1; i <= n; i++) {
        ans += (pow2 * max_with[i].first) % MOD;
        ans %= MOD;

        pow2 *= 2;
        pow2 %= MOD;
    }

    cout << ans << endl;
}