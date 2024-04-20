#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
using i64 = long long;

i64 n, x, a, y, b, k;
vector<i64> tickets;

bool check(i64 tickets_sold) {
    i64 both = 0;
    i64 a_only = 0;
    i64 b_only = 0;
    for (i64 i = 1; i <= tickets_sold; i++) {
        if (i % a == 0 && i % b == 0) both++;
        else if (i % a == 0) a_only++;
        else if (i % b == 0) b_only++;
    }

    i64 i = 1;
    i64 contrib = 0;

    for (i64 v = 1; v <= both; v++) {
        contrib += tickets[i] * (x + y);
        i++;
        if (contrib >= k) return true;
    }

    for (i64 v = 1; v <= a_only; v++) {
        contrib += tickets[i] * x;
        i++;
        if (contrib >= k) return true;
    }

    for (i64 v = 1; v <= b_only; v++) {
        contrib += tickets[i] * y;
        i++;
        if (contrib >= k) return true;
    }

    return contrib >= k;
}

void solve() {
    tickets.clear();

    cin >> n;
    tickets.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> tickets[i];
        tickets[i] /= 100;
    }
    std::sort(tickets.begin() + 1, tickets.end());
    std::reverse(tickets.begin() + 1, tickets.end());
    cin >> x >> a >> y >> b >> k;

    if (x < y) {
        std::swap(x, y);
        std::swap(a, b);
    }

    if (check(n) == false) {
        printf("-1\n");
        return;
    }

    i64 lo = 1;
    i64 hi = n;
    while (lo < hi) {
        i64 mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    printf("%lld\n", lo);
}

int main(void) {
    int Q; cin >> Q;
    while (Q--) solve();
}
