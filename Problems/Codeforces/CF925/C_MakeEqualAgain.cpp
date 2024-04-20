#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    int pre_eq = 0;
    int suf_eq = 0;

    for (int i = 1; i <= n; i++) {
        if (a[i] == a[1]) pre_eq++;
        else break;
    }

    for (int i = n; i >= 1; i--) {
        if (a[i] == a[n]) suf_eq++;
        else break;
    }

    if (a[1] != a[n]) {
        printf("%d\n", n - max(pre_eq, suf_eq));
    } else {
        printf("%d\n", n - min(n, pre_eq + suf_eq));
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}