#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

void solve() {
    int N; cin >> N;
    vector<int> a(N, 0);

    int total = 0;
    for (int i = 0; i < N; i++) {
        // printf("%d\n", i);
        // fflush(stdout);
        cin >> a[i];
        total += a[i];
    }

    // printf("before ( total = %d )\n", total);
    // fflush(stdout);

    int best = 1e9;

    // enumerate divisors
    for (int x = 0; x <= total; x++) {
        if (x != 0 && total % x != 0) continue;

        int n_merges = 0;

        // printf("starting, x = %d\n", x);
        // fflush(stdout);

        // merge in a greedy way
        int merge = a[0];
        for (int i = 1; i < N; i++) {
            // printf("i = %d\n", i);
            // fflush(stdout);
            if (merge < x) {
                // printf("combined merge = %d with a[%d] = %d\n", merge, i, a[i]);
                merge += a[i];
                n_merges++;
            } else if (merge > x) {
                goto stop_merge;
            } else if (merge == x) {
                merge = a[i];
            }
        }

        // final merge successful
        if (merge == x) {
            // printf("merge count for a[.] = %d is %d\n", x, n_merges);
            best = min(best, n_merges);
        }

        // printf("exiting\n");
        // exit(-1);

        stop_merge: (void) 1;
    }

    cout << best << endl;
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
}
