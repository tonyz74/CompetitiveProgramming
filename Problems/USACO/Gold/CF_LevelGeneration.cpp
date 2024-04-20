#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

bool can_build(i64 n, i64 mid) {
    i64 n_bridges = mid / 2;
    if (mid % 2 != 0) n_bridges++;

    // e, f, g -> a -> b -> c -> d
    // n_bridges takes up n vertices

    if (n <= n_bridges) return false;

    // a b -> c -> d
    i64 remaining_vertices = n - n_bridges - 1;
    if (n_bridges == n - 1) remaining_vertices = 0;

    // printf("(%lld) remain: %lld\n", mid, remaining_vertices);

    i64 edges_left = mid - n_bridges;

    i64 max_remain = ((remaining_vertices + 1) * (remaining_vertices)) / 2;
    return max_remain >= edges_left;
}

void solve() {
    i64 n; cin >> n;

    i64 lo = 0;
    i64 hi = (n * (n - 1)) / 2;

    // printf("%d\n", can_build(n, 3));
    
    // find last true
    while (lo < hi) {
        i64 mid = (lo + hi + 1) / 2;

        if (can_build(n, mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    // printf("%lld total edges\n", lo);
    printf("%lld\n", lo);
}

int main(void) {
    int t; cin >> t;
    for (int i = 0; i < t; i++) solve();
}