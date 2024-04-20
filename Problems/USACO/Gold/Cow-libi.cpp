#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;


struct point {
    i64 x, y;

    point() {}
    point(i64 horizontal, i64 vertical): x(horizontal), y(vertical) {}

    bool operator<(const point& rhs) const {
        return make_pair(x, y) < make_pair(rhs.x, rhs.y);
    }

    bool operator==(const point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    i64 dist_squared(const point& other) const {
        i64 x_off = other.x - x;
        i64 y_off = other.y - y;

        return x_off * x_off + y_off * y_off;
    }
};

void dbg(const pair<i64, point> pairing) {
    printf("[time: %lld] (x=%lld, y=%lld)", pairing.first, pairing.second.x, pairing.second.y);
}

bool can_reach_within_time(pair<i64, point> info1, pair<i64, point> info2) {
    i64 time_diff = info1.first - info2.first;

    if (time_diff * time_diff < info1.second.dist_squared(info2.second)) {
        return false;
    }
    return true;
}

int main(void) {
    int G; cin >> G;
    int N; cin >> N;

    vector<pair<i64, point> > grazings(G);
    vector<pair<i64, point> > alibis(N);
    
    for (int i = 0; i < G; i++) {
        cin >> grazings[i].second.x >> grazings[i].second.y >> grazings[i].first;
    }
    std::sort(grazings.begin(), grazings.end());

    for (int i = 0; i < N; i++) {
        cin >> alibis[i].second.x >> alibis[i].second.y >> alibis[i].first;
    }

    int good_alibis = 0;

    for (int alb = 0; alb < N; alb++) {
        i64 alibi_time = alibis[alb].first;
        point alibi_pos = alibis[alb].second;

        pair<i64, point> search = make_pair(alibi_time, point());
        auto lower = std::lower_bound(grazings.begin(), grazings.end(), search);

        // if i'm past the end (i.e. my alibi time is after any grazing)
        if (lower == grazings.end()) {
            if (!can_reach_within_time(grazings.back(), alibis[alb])) {
                good_alibis++;
            }
            continue; 
        }

        if (lower->first == alibi_time) {
            // if we're at the time of a grazing, we can immediately tell if we're
            // a possible suspect or not. if we're not at the grazing location
            // we're immediately safe.
            if (lower->second == alibi_pos) {
                continue;
            } else {
                good_alibis++;
                continue;
            }
        }

        i64 i = lower - grazings.begin();

        // check the one after
        if (!can_reach_within_time(grazings[i], alibis[alb])) {
            good_alibis++;
            continue;
        }

        if (i != 0) {
            // check before
            if (!can_reach_within_time(grazings[i - 1], alibis[alb])) {
                good_alibis++;
                continue;
            }
        }
    }

    cout << good_alibis << endl;
}