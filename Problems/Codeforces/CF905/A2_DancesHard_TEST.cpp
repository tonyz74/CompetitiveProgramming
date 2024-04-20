#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void solve() {
    int n, m; cin >> n >> m;

    vector<int> sto(n + 1);
    for (int i = 2; i <= n; i++) cin >> sto[i];

    vector<int> b(n + 1);
    for (int i = 1; i <= n; i++) cin >> b[i];
    std::sort(b.begin() + 1, b.end());

    set<int> uniq_sols;

    for (int k = 1; k <= m; k++) {
        vector<int> a = sto;
        a[1] = k;
        std::sort(a.begin() + 1, a.end());

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

        uniq_sols.insert(l - 1);
        // printf("%d\n", l - 1);
    }

    if (uniq_sols.size() > 2) printf("WHAT\n");
    cout << uniq_sols.size() << endl;
    // assert(uniq_sols.size() <= 2);
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}