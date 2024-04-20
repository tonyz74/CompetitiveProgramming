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

    int fin;
    int n_occ_1s = 0;
    for (fin = 0; fin < n; fin++) {
        // alice will pick this last, as it's safest to leave
        if (!occ[fin]) {
            break;
        }

        if (occ[fin] == 1) {
            n_occ_1s++;
        }

        // will remove this one
        if (n_occ_1s == 2) {
            break;
        }
    }

    cout << fin << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}