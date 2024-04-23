#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <bitset>

using namespace std;
using i64 = long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> prefix_xor(n + 1);
    for (int i = 1; i <= n; i++) {
        prefix_xor[i] = prefix_xor[i - 1] ^ a[i];
    }

    auto f = [&] (i64 l, i64 r) {
        return prefix_xor[r] ^ prefix_xor[l - 1];
    };

    vector<vector<i64> > pfx_zero_at(n + 1, vector<i64>(30, 0));
    vector<vector<i64> > pfx_one_at(n + 1, vector<i64>(30, 0));

    vector<vector<i64> > sfx_zero_at(n + 2, vector<i64>(30, 0));
    vector<vector<i64> > sfx_one_at(n + 2, vector<i64>(30, 0));

    for (int i = 1; i <= n; i++) {
        for (int bit = 29; bit >= 0; bit--) {
            if ((a[i] & (1ll << bit)) == 0) {
                pfx_zero_at[i][bit] = pfx_zero_at[i - 1][bit] + 1;
                pfx_one_at[i][bit] = pfx_one_at[i - 1][bit];
            } else {
                pfx_one_at[i][bit] = pfx_zero_at[i - 1][bit] + 1;
                pfx_zero_at[i][bit] = pfx_one_at[i - 1][bit];
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        for (int bit = 29; bit >= 0; bit--) {
            if ((a[i] & (1ll << bit)) == 0) {
                sfx_zero_at[i][bit] = sfx_zero_at[i + 1][bit] + 1;
                sfx_one_at[i][bit] = sfx_one_at[i + 1][bit];
            } else {
                sfx_one_at[i][bit] = sfx_zero_at[i + 1][bit] + 1;
                sfx_zero_at[i][bit] = sfx_one_at[i + 1][bit];
            }
        }
    }

    i64 ans = 0;
    (void) f;

    for (int y = 1; y <= n; y++) {
        int msb = 0;
        for (int bit = 29; bit >= 0; bit--) {
            if (a[y] & (1ll << bit)) {
                msb = bit;
                break;
            }
        }

        ans += (pfx_zero_at[y - 1][msb] + 1) * sfx_one_at[y + 1][msb];
        ans += pfx_one_at[y - 1][msb] * (sfx_zero_at[y + 1][msb] + 1);
    }

    cout << ans << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}