#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    int avg = sum / n;

    for (int i = 1; i <= n - 1; i++) {
        if (a[i] < avg) {
            printf("NO\n");
            return;
        }

        int extra = a[i] - avg;
        a[i] -= extra;
        // donate extra to the next one
        a[i + 1] += extra;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] != avg) {
            printf("NO\n");
            return;
        }
    }

    printf("YES\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();    
}