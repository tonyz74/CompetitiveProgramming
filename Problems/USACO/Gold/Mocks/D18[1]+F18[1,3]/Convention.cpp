#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
using i64 = long long;

i64 N, M, C;
vector<pair<i64, i64> > arrivals;
// values x in waiting: waiting since time x, so we want min

bool check(i64 max_wait_time) {
    // bus either leaves when it's forced to leave, or if it's full
    i64 cap_used = 0;
    i64 buses_used = 0;
    i64 must_leave_by = -1;

    for (i64 i = 1; i <= N; i++) {
        i64 arrival_time = arrivals[i].first;

        // if it's latest leaving time has already passed, it must go
        if (must_leave_by != -1 && must_leave_by < arrival_time) {
            cap_used = 0;
            buses_used++;
            must_leave_by = -1;
        }

        if (must_leave_by == -1) {
            must_leave_by = arrival_time + max_wait_time;
        }

        cap_used++;
        if (cap_used == C) {
            cap_used = 0;
            buses_used++;
            must_leave_by = -1;
        }
    }
    
    if (cap_used != 0) {
        buses_used++;
        cap_used = 0;
    }

    return buses_used <= M;
}

int main(void) {
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);

    cin >> N >> M >> C;
    arrivals.resize(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> arrivals[i].first;
        arrivals[i].second = i;
    }

    std::sort(arrivals.begin() + 1, arrivals.end());

    i64 lo = 1;
    i64 hi = 1e9;

    // find first true
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