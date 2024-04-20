#include <iostream>
#include <vector>
#include <map>

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n + 1);
    map<int, int> occ;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        occ[a[i]]++;
    }

    if ((int) occ.size() == 1) {
        printf("-1\n");
        return;
    }

    int filler = 0;
    for (auto p: occ) {
        if (filler == 0 || p.second > occ[filler]) {
            filler = p.first; 
        }
    }

    vector<int> neq_filler;
    for (int i = 1; i <= n; i++) {
        if (a[i] != filler) {
            neq_filler.push_back(i);
        }
    }

    int min_ops = 1e9;
    for (int i = 0; i < (int) (neq_filler.size()); i++) {
        int me_pos = neq_filler[i];
        if (i < (int) (neq_filler.size() - 1)) {
            int next_pos = neq_filler[i + 1];
            int dist = next_pos - me_pos - 1;
            min_ops = min(min_ops, dist);
        }

        min_ops = min(min_ops, me_pos - 1);
        min_ops = min(min_ops, n - me_pos);
    }

    cout << min_ops << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}