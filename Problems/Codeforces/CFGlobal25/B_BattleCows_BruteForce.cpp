#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> ratings(n + 1);
    for (int i = 1; i <= n; i++) cin >> ratings[i];

    int ours = ratings[k];

    int best = 0;
    for (int swp = 1; swp <= n; swp++) {
        std::swap(ratings[swp], ratings[k]);

        int ok = 0;
        int start_me = 0;
        int mx = 0;

        for (int i = 1; i <= n; i++) {
            mx = max(mx, ratings[i]);
            if (mx == ours) {
                if (start_me) {
                    ok++;
                } else if (!start_me && i != 1) {
                    ok++;
                }

                start_me = true;
            }
        }

        std::swap(ratings[k], ratings[swp]);

        best = max(best, ok);
    }

    printf("%d\n", best);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}