#include <iostream>
#include <vector>
#include <set>

using namespace std;

using i64 = long long;

struct region {
    i64 start;
    i64 end;

    bool operator<(const region& rhs) const {
        return make_pair(end, start) < make_pair(rhs.end, rhs.start);
    }
};

i64 N, M;
set<region> intervals;

bool can_construct(i64 dist) {
    region front = *intervals.begin();

    i64 current_pos = front.start;
    // put at front.start
    for (int i = 1; i < N; i++) {
        i64 target_pos = current_pos + dist;

        region target;
        target.start = 0;
        target.end = target_pos;

        auto it = intervals.lower_bound(target);
        auto closest_reg = *it;

        if (it == intervals.end()) {
            return false;
        }

        if (closest_reg.start > target_pos) {
            target_pos = closest_reg.start;
        }

        current_pos = target_pos;
    }

    return true;
}

int main(void) {
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);

    cin >> N >> M;
    
    for (i64 i = 0; i < M; i++) {
        region reg;
        cin >> reg.start >> reg.end;

        intervals.insert(reg);
    }

    i64 lo = 1;
    i64 hi = 1e18;

    while (lo < hi) {
        i64 mid = (lo + hi + 1) / 2;

        if (can_construct(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << endl;

}