#include <iostream>
#include <vector>
#include <set>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<int> not_there;
    not_there.insert(n);

    for (int i = n - 1; i >= 0; i--) {
        int mex = *not_there.begin();
        p[i] = mex - a[i];
        not_there.insert(p[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("%d", p[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}