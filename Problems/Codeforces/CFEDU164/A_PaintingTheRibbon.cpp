#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, m, k; cin >> n >> m >> k;

    vector<int> parts(n + 1);
    int col = 1;
    for (int i = 1; i <= n; i++) {
        parts[i] = col;
        col++;
        if (col == m + 1) col = 1;
    }

    int mx = 0;
    vector<int> colors(m + 1);
    for (int i = 1; i <= n; i++) {
        colors[parts[i]]++;
        mx = max(colors[parts[i]], mx);
    }

    int rem = n - mx;
    if (rem <= k) {
        printf("NO\n");
    } else {
        printf("YES\n");
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}