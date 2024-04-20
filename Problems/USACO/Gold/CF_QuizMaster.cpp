#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i]; 

    std::sort(a.begin(), a.end());

    vector<int> n_facs(m + 1);
    vector<vector<int> > factors(n);

    for (int i = 0; i < n; i++) {
        for (int fac = 1; fac * fac <= a[i]; fac++) {
            if (a[i] % fac == 0) {
                if (fac <= m) {
                    factors[i].push_back(fac);
                    n_facs[fac]++;
                }

                int other = a[i] / fac;
                if (other != fac && other <= m) {
                    factors[i].push_back(other);
                    n_facs[other]++;
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        if (n_facs[i] == 0) {
            printf("-1\n");
            return;
        }
    }

    // for (int i = 0; i < n; i++) {
    //     printf("%d: ", a[i]);
    //     for (int f: factors[i]) {
    //         printf("%d, ", f);
    //     }
    //     printf("\n");
    // }

    int min_diff = 1e9;

    vector<int> window(m + 1);
    int n_missing = m;

    vector<bool> seen(n + 1, false);

    int j = 0;
    for (int i = 0; i < n; i++) {
        if (j < i) j = i;

        if (!seen[i]) {
            for (int f: factors[i]) {
                if (window[f] == 0) n_missing--;
                window[f]++;
            }
            seen[i] = true;
        }

        while (j != n - 1 && n_missing != 0) {
            j++;

            if (!seen[j]) {
                for (int f: factors[j]) {;
                    if (window[f] == 0) n_missing--;
                    window[f]++;
                }
                seen[j] = true;
            }
        }

        if (n_missing == 0) {
            min_diff = min(min_diff, a[j] - a[i]);
        }

        // remove the current ones in i
        for (int f: factors[i]) {
            if (window[f] == 1) n_missing++;
            window[f]--;
            seen[i] = false;
        }
    }

    cout << min_diff << endl;
}

int main(void) {
    int t; cin >> t;
    for (int i = 0; i < t; i++) solve();
}