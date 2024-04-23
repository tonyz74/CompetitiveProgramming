#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

void solve() {
    i64 n, k; cin >> n >> k;

    i64 curr_sum = 0;
    vector<i64> res;

    i64 bit = 0;
    for (i64 i = 0; i < n - 1; i++) {
        i64 new_val = 0;
        i64 mask = (1ll << bit);
        while (curr_sum + mask <= k) {
            new_val += mask;
            curr_sum += mask;
            bit++;
            mask = (1ll << bit);
        }

        res.push_back(new_val);
    }

    // last one
    res.push_back(k - curr_sum);

    for (int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}