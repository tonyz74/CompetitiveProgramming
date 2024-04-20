#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

void solve() {
    i64 n, k; cin >> n >> k;

    if (k > n) {
        printf("NO\n");
        return;
    } else if (k == n) {
        printf("YES\n1\n1\n");
        return;
    } else {
        if (2 * k <= n + 1) {
            printf("YES\n");
            printf("2\n%lld 1\n", n - k + 1);
        } else {
            printf("NO\n");
        }
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}