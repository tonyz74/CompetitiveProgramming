#include <iostream>
#include <vector>
#include <set>

using namespace std;

void solve() {
    int n; cin >> n;
    int n_1 = 0;

    set<int> missing;

    for (int i = 1; i <= n; i++) {
        missing.insert(i);
    }

    vector<int> h(n);
    for (int i = 1; i < n; i++) {
        cin >> h[i];
        n_1 += h[i] == 1;
        missing.erase(h[i]);
    }

    if (missing.size() > 2) {
        printf("-1\n");
        return;
    } else if (missing.size() == 1) {
        // no repeated elements, can directly recreate
        if (h[n - 1] != 1) {
            printf("-1\n");
            return;
        }

        printf("1 ");
        for (int i = n - 2; i >= 1; i--) {
            printf("%d ", h[i]);
        }
        printf("%d\n", *missing.begin());
        return;
    }

    if (n_1 != 2 || h[n - 1] != 1) {
        printf("-1\n");
        return;
    }

    // to take min with
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n; i++) ans[i] = 1e9;

    int a = *missing.begin(), b = *missing.rbegin();
    int configs[2][2] = {{ a, b }, { b, a }};

    for (int cfg = 0; cfg < 2; cfg++) {
        int front = configs[cfg][0];
        int back = configs[cfg][1];

        vector<int> test(n + 1, 0);
        test[1] = front; test[n] = back;
        int l = 1, r = n;

        for (int i = 1; i <= n - 1; i++) {
            if (test[l] < test[r]) {
                test[--r] = h[i];
            } else {
                test[++l] = h[i];
            }
        }

        ans = min(ans, test);
    }

    for (int i = 1; i <= n; i++) {
        printf("%d", ans[i]);
        if (i != n) printf(" ");
        else printf("\n");
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}