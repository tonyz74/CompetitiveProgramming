#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
using i64 = long long;

void solve() {
    i64 N, M; cin >> N >> M;

    i64 ans = 0;
    for (i64 x = 1; x * x <= N; x++) {
        for (i64 y = 1; y * y <= M; y++) {
            if (gcd(x, y) != 1) continue;

            ans += min(N / (x * (x + y)), M / (y * (x + y)));
        }
    }

    cout << ans << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}
