#include <iostream>
#include <vector>
#include <set>

using namespace std;

void solve() {
    set<int> valid_k;
    int n, v; cin >> n >> v;
    // ascending: if i am near the start of a (2k - 2) period
    int nearest_end_asc = -1;
    // descending: if i am near the end of a (2k - 2) period
    int nearest_end_dsc = -1;

    // two cases: if v == 1 we have to handle separately
    if (v == 1) {
        nearest_end_asc = n - 1;
        nearest_end_dsc = -1;
    } else {
        // we have to get all the way from this to a 1, so v steps
        nearest_end_asc = n - v;
        // we end at a 2 so we only need v - 2 steps to the right
        nearest_end_dsc = n + (v - 2);

        if (nearest_end_asc <= 0) {
            nearest_end_asc = -1;
        }
    }

    vector<int> ends = { nearest_end_asc, nearest_end_dsc };
    for (int e: ends) {
        if (e == -1 || e % 2 != 0) continue;
        // printf("gap: %d\n", e);

        // a(k - 1) = e/2
        // factorize this, find all k
        int X = e / 2;
        for (int i = 1; i * i <= X; i++) {
            if (X % i == 0) {
                if (i + 1 >= v) {
                    valid_k.insert(i + 1);
                }
                if (X / i + 1 >= v) {
                    valid_k.insert(X / i + 1);
                }
            }
        }
    }

    printf("%d\n", (int) valid_k.size());
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}