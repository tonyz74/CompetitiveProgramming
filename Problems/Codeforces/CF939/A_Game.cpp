#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int k, q; cin >> k >> q;
    vector<int> a(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }

    for (int x = 1; x <= q; x++) {
        int n; cin >> n;
        // either the smallest one in a, minus 1, or myself
        int ans = min(n, a[1] - 1);
        printf("%d ", ans);
    }
    printf("\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}