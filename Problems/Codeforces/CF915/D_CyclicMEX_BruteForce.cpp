#include <iostream>
#include <vector>
#include <set>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        printf("%d ", a[i]);
    }
    printf("\n");

    int ans = 0;
    vector<vector<int> > best_v;

    for (int start = 0; start < n; start++) {
        vector<int> res;

        int ans_now = 0;
        set<int> unused;
        for (int i = 0; i <= n; i++) unused.insert(i);

        int elem = start;
        for (int cnt = 0; cnt < n; cnt++) {
            res.push_back(a[elem]);

            unused.erase(a[elem]);
            ans_now += *unused.begin();

            elem++;
            if (elem == n) elem = 0;
        }

        if (ans_now > ans) {
            ans = ans_now;
            best_v.clear();
        }
        
        if (ans_now == ans) {
            best_v.push_back(res);
        }
    }

    cout << ans << endl;
    for (auto v: best_v) {
        for (int x: v) {
            printf("%d ", x);
        }
        printf("\n");
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}