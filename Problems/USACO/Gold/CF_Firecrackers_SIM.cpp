#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, a, b;
vector<int> fc;

// always optimal to first throw down all the firecrackers then run
bool check(int to_detonate) {
    int guard = b;
    int hooligan = a;

    int mx_time = 0;
    int sec = 1;
    for (int i = to_detonate; i >= 1; i--) {
        if (guard == hooligan) {
            // printf("caught\n");
            return false;
        }

        // printf("detonating %d, will detonate at time %d\n", fc[i], sec + fc[i]);
        mx_time = max(mx_time, sec + fc[i]);
        guard--;
        sec++;
    }

    // spent `to_detonate` time to throw down all the firecrackers
    while (guard != hooligan) {
        if (hooligan != 1) hooligan--;
        guard--;
        if (guard == hooligan) break;

        sec++;
    }

    return sec >= mx_time;
}

void solve() {
    cin >> n >> m >> a >> b;

    if (a > b) {
        a = n - a + 1;
        b = n - b + 1;
    }

    fc.clear(); fc.resize(m + 1);
    for (int i = 1; i <= m; i++) cin >> fc[i];
    // throwing low detonation time firecrackers is always optimal
    std::sort(fc.begin() + 1, fc.end());

    // printf("%d\n", check(2));
    // return;

    int lo = 0;
    int hi = min(m, b - a - 1);

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
    while (t--) solve();
}