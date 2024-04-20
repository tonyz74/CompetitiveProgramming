#include <iostream>
#include <vector>
#include <map>

using namespace std;
using i64 = long long;

void solve() {
    i64 n, k; cin >> n >> k;
    vector<i64> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    i64 shift = 0;
    vector<i64> seen(n + 1);

    i64 remaining = k;
    while (remaining--) {
        i64 back_i = (shift + n - 1) % n;
        // printf("shift %lld, %lld\n", shift, b[back_i]);

        // cycled to have the same index as the back
        if (seen[back_i]) {
            printf("YES\n");
            return;
        }
        seen[back_i] = true;

        if (b[back_i] > n) {
            printf("NO\n");
            return;
        }

        shift = back_i - (b[back_i] - 1);
    }

    printf("YES\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}