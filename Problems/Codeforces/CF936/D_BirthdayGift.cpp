#include <iostream>
#include <vector>

using namespace std;

#define int long long

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // we're calculating max k when ans < x,
    // so convert to ans < x + 1 for ans <= x
    x++;

    int ans = -1;

    // be careful of this 31, though x < 2^30, we ++, so 2^30 is possible
    for (int i = 0; i < 31; i++) {
        if (x & (1 << i)) {
            int n_zeroes = 0;
            int xor_sum = 0;

            for (int j = 0; j < n; j++) {
                int x2 = x ^ (1 << i);  // first set the ith bit to 0

                // then i want only the values that are on in a[j] but shouldn't be on,
                // (so x doesnt have them on in places higher than i), and disregard
                // anything in a lower bit
                int v = (a[j] & (~x2)) & (~((1 << i) - 1));

                xor_sum ^= v;
                n_zeroes += (xor_sum == 0);
            }

            if (xor_sum == 0) {
                ans = max(ans, n_zeroes);
            }

        }
    }

    cout << ans << endl;
}

signed main(void) {
    int t; cin >> t;
    while (t--) solve();
}