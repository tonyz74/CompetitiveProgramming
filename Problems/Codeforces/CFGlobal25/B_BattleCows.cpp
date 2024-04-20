#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> ratings(n + 1);
    vector<pair<int, int> > pfx_max(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> ratings[i];
    }

    for (int i = 1; i <= n; i++) {
        if (ratings[i] > pfx_max[i - 1].first) {
            pfx_max[i].first = ratings[i];
            pfx_max[i].second = pfx_max[i - 1].first;
        } else {
            pfx_max[i].first = pfx_max[i - 1].first;
            pfx_max[i].second = max(pfx_max[i - 1].second, ratings[i]);
        }

        // printf("%d: %d %d\n", i, pfx_max[i].first, pfx_max[i].second);
    }

    int by_self = 0;
    for (int i = 1; i <= n; i++) {
        if (pfx_max[i].first <= ratings[k]) {
            by_self = i;
        }
    }

    int fail1 = -1;
    int fail2 = -1;
    for (int i = 1; i < k; i++) {
        if (pfx_max[i].first > ratings[k]) {
            if (fail1 == -1) fail1 = i;
            if (pfx_max[i].second > ratings[k] && fail2 == -1) fail2 = i;
        }
    }
    fail1 = (fail1 == -1) ? k : fail1;
    fail2 = (fail2 == -1) ? k : fail2;

    // swap k with pos i
    // printf("%d %d\n", fail1, fail2);

    int best = 0;
    for (int i = 1; i < k; i++) {

        pair<int, int> mx = pfx_max[i];

        int val = mx.first;
        if (mx.first == ratings[i]) {
            val = mx.second;
        } else {
            val = mx.first;
        }

        if (ratings[k] >= val) {
            int nearest_fail = fail1;
            if (i == fail1) nearest_fail = fail2;

            if (i == 1) best = max(best, nearest_fail - i - 1);
            else best = max(best, nearest_fail - i);
        }
    }

    printf("%d\n", max(max(best, by_self - 1), 0));
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}