#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, l; cin >> n >> l;
    vector<int> a(n + 1);
    vector<int> b(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cin >> b[i];
    }

    auto check = [&] (int k) {
        int found = false;

        function<void(int, int, vector<int>)> fn = [&] (int i, int picked, vector<int> v) {
            if (found == true) return;

            if (picked == k) {
                int tot = 0;
                vector<int> vals;

                for (int j: v) {
                    tot += a[j];
                    vals.push_back(b[j]);
                }
                std::sort(vals.begin(), vals.end());

                for (int j = 0; j < k - 1; j++) {
                    tot += abs(vals[j] - vals[j + 1]);
                }

                if (tot <= l) {
                    // for (int j = 0; j < k; j++) {
                    //     printf("%d,%d ", a[v[j]], b[v[j]]);
                    // }
                    // printf("\n");
                    found = true;
                }
                return;
            }

            if (i == n + 1) {
                return;
            }

            fn(i + 1, picked, v);

            v.push_back(i);
            fn(i + 1, picked + 1, v);
        };

        fn(1, 0, vector<int>());

        return found;
    };

    int lo = 0; int hi = n;
    // find last true
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    printf("%d\n", lo);
}

int main(void) {
    int t; cin >> t;
    // int tmax = t;
    while (t--) {
        // printf("test case %d\n", tmax - t);
        solve();
    }
}
