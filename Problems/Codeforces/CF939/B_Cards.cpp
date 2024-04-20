#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    vector<int> occ(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        occ[a[i]]++;
    }

    int my_score = 0;
    for (int i = 1; i <= n; i++) {
        if (occ[i] == 2) {
            my_score++;
        }
    }

    printf("%d\n", my_score);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}