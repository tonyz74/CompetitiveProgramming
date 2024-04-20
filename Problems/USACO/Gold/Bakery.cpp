#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

struct request {
    i64 cookies;
    i64 muffins;
    i64 wait_time;
};

i64 N, cookie_time, muffin_time;
vector<request> requests;

bool satisfies(i64 total_upgrade_cost) {
    // trying to find a valid cookie time

    // we cannot go under paying total_upgrade_cost times
    i64 smallest = max(1ll, cookie_time - total_upgrade_cost);
    i64 largest = min(cookie_time + muffin_time - total_upgrade_cost - 1, cookie_time);

    i64 precompute = cookie_time + muffin_time - total_upgrade_cost;

    for (request rq: requests) {
        if (rq.cookies == rq.muffins) {
            if (rq.wait_time - rq.muffins * (precompute) < 0) {
                return false;
            }
            continue;
        }

        // printf("rq: %lld, %lld, wait: %lld\n", rq.cookies, rq.muffins, rq.wait_time);

        if (rq.cookies > rq.muffins) {
            // the v_c <= rhs
            i64 value = (rq.wait_time - rq.muffins * precompute) / (rq.cookies - rq.muffins);
            largest = min(largest, value);

        } else if (rq.muffins > rq.cookies) {
            // the v_c >= rhs
            i64 numer = (rq.wait_time - rq.muffins * precompute);
            i64 denom = (rq.cookies - rq.muffins);

            i64 value = numer / denom;
            if (numer % denom != 0) {
                value++;
            }

            smallest = max(smallest, value);
        }

        // printf("%lld %lld\n", smallest, largest);
    }

    return (smallest <= largest);
}

void solve() {
    cin >> N >> cookie_time >> muffin_time;
    requests.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> requests[i].cookies >> requests[i].muffins >> requests[i].wait_time;
    }

    // maximum cost would be to upgrade them to max level (each costs 1 only)
    i64 high = cookie_time + muffin_time - 2;
    // minimum cost would be just spending nothing
    i64 low = 0;

    // printf("%d\n", (int) satisfies(5));
    // return;

    while (low < high) {
        i64 mid = (low + high) / 2;

        // we want to find the first true
        if (satisfies(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    cout << low << endl;
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        requests.clear();
        solve();
    }
}