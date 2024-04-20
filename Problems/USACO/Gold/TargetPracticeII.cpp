#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

struct rect {
    i64 bottom;
    i64 top;
    i64 right;
};

struct point {
    i64 x, y;
    point(i64 hor, i64 ver): x(hor), y(ver) {}
};

void solve() {
    i64 N, X1; cin >> N >> X1;

    vector<i64> undecided;

    vector<i64> neg_slopes;
    vector<point> neg_points;

    vector<i64> pos_slopes;
    vector<point> pos_points;

    for (i64 i = 1; i <= N; i++) {
        i64 bt, tp, rt;
        cin >> bt >> tp >> rt;
        neg_points.push_back(point(rt, tp));
        pos_points.push_back(point(rt, bt));

        undecided.push_back(bt);
        undecided.push_back(tp);
    }

    for (i64 i = 1; i <= N * 4; i++) {
        i64 x; cin >> x;
        if (x < 0) neg_slopes.push_back(x);
        if (x > 0) pos_slopes.push_back(x);
    }

    if ((i64) neg_slopes.size() < N || (i64) pos_slopes.size() < N) {
        cout << -1 << endl;
        return;
    }


    i64 neg_remain = neg_slopes.size() - N;
    std::sort(undecided.begin(), undecided.end());

    // we can figure out the pos and neg values based on the position
    i64 i = 0;
    for (; i < neg_remain; i++) {
        i64 lowest = undecided[i];
        neg_points.push_back(point(X1, lowest));
    }
    for (; i < (i64) undecided.size(); i++) {
        i64 higher = undecided[i];
        pos_points.push_back(point(X1, higher));
    }

    // we want -2 before -1
    std::sort(neg_slopes.begin(), neg_slopes.end());
    std::reverse(neg_slopes.begin(), neg_slopes.end());
    // we want 1 before 2
    std::sort(pos_slopes.begin(), pos_slopes.end());

    // preprocessing done

    auto check_max = [&] (i64 test_max) {
        vector<i64> req_slopes;

        // loop through all points that will use a negatively sloped s_i to
        // be hit by a cow, compute "cheapest" slope needed to do so.
        for (point p: neg_points) {
            if (test_max <= p.y) return false;
            i64 highest_allowed_s = (test_max - p.y) / p.x;
            req_slopes.push_back(highest_allowed_s);
        }

        // 1, 2, 3, 4, ...
        std::sort(req_slopes.begin(), req_slopes.end());

        // neg slopes: -1, -2, -3, ...
        for (i64 i = 0; i < (i64) neg_slopes.size(); i++) {
            if (req_slopes[i] < abs(neg_slopes[i])) {
                return false;
            }
        }

        return true;
    };

    auto check_min = [&] (i64 test_min) {
        vector<i64> req_slopes;

        for (point p: pos_points) {
            if (test_min >= p.y) return false;
            i64 highest_allowed_s = (p.y - test_min) / p.x;
            // printf("%lld %lld => %lld\n", p.x, p.y, highest_allowed_s);
            req_slopes.push_back(highest_allowed_s);
        }

        std::sort(req_slopes.begin(), req_slopes.end());

        for (i64 i = 0; i < (i64) pos_slopes.size(); i++) {
            // printf("%lld, %lld\n", req_slopes[i], pos_slopes[i]);
            if (req_slopes[i] < pos_slopes[i]) {
                return false;
            }
        }

        return true;
    };

    i64 best_max = 0;
    {
        i64 lo = -4e18;
        i64 hi = +4e18;

        // be careful with c++ binary search with negative values!
        // -3/2 is -1, not -2, it doesn't go "down", it removes the fractional part.
        while (lo < hi) {
            i64 dbl_mid = lo + hi;
            i64 mid = dbl_mid / 2;
            if (dbl_mid < 0 && dbl_mid % 2 == 1) {
                mid--;
            }

            if (check_max(mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        best_max = lo;
    }

    i64 best_min = 0;
    {
        i64 lo = -4e18;
        i64 hi = +4e18;

        // this is actually ok, because the only case where the rounding
        // actually matters is when they're right next to each other,
        // and that case will round correctly (up).
        while (lo < hi) {
            i64 mid = (lo + hi + 1) / 2;
            if (check_min(mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        best_min = lo;
    }

    cout << (best_max - best_min) << endl;
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}