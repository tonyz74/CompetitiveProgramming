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

    int i = 1;
    int l = 1, r = 1;

    while (r <= n) {
        if (a[i] < b[r]) {
            r++;
            i++;
        } else {
            l++;
            r++;
        }
    }

    printf("%d\n", l - 1);
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}