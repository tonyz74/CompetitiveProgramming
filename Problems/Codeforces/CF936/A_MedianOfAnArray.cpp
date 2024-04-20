#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    std::sort(a.begin() + 1, a.end());

    int m = (n / 2);
    if (n % 2 == 1) m++;


    int cnt = 0;
    int i = m;
    while (i <= n && a[i] == a[m]) {
        i++;
        cnt++;
    }

    printf("%d\n", cnt);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}