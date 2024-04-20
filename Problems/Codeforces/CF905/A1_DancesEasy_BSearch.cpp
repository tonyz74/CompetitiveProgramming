#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, m; cin >> n >> m;

    vector<int> a(n + 1); a[1] = 1;
    for (int i = 2; i <= n; i++) cin >> a[i];
    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) cin >> b[i];

    std::sort(a.begin() + 1, a.end());
    std::sort(b.begin() + 1, b.end());

    int lo = 0; int hi = n;

    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", a[i]);
    // }
    // printf("\n");
    // for (int i = 1; i <= n; i++) {
    //     printf("%d ", b[i]);
    // }
    // printf("\n");

    // printf("...\n\n");

    // m is the number to remove
    auto check = [&] (int m) {
        vector<int> x(1), y(1);
        for (int i = 1; i <= n - m; i++) {
            x.push_back(a[i]);
        }
        for (int i = 1; i <= n - m; i++) {
            y.push_back(b[n - (i - 1)]);
        }
        std::reverse(y.begin() + 1, y.end());

        for (int i = 1; i <= n - m; i++) {
            if (x[i] >= y[i]) return false;
        }

        return true;
    };

    // find first true
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << endl;
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}