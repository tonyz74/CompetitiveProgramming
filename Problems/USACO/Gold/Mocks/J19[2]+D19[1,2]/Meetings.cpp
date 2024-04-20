#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;
using i64 = long long;

struct cow {
    i64 pos;
    i64 dir;
    i64 wt;

    cow() {}
    cow(i64 p, i64 d, i64 w): pos(p), dir(d), wt(w) {}
    bool operator<(const cow& rhs) const {
        return pos < rhs.pos;
    }
};

int main(void) {
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);

    i64 N, L; cin >> N >> L;

    i64 weight_sum = 0;
    vector<cow> cows(N + 1);

    for (i64 i = 1; i <= N; i++) {
        i64 w, x, d; cin >> w >> x >> d;
        weight_sum += w;
        cows[i] = (cow(x, d, w));
    }

    std::sort(cows.begin() + 1, cows.end());
    
    // leftgoers
    deque<cow> going_right;
    map<i64, i64> left_arrivals;
    for (i64 i = 1; i <= N; i++) {
        // trying to go left, will swap with the earliest previous one going right
        if (cows[i].dir == -1) {
            if (going_right.empty()) {
                left_arrivals[cows[i].pos] += (cows[i].wt);
            } else {
                cow swapped = cows[i];
                swapped.dir = 1;
                cow earliest_rightgoer = going_right.front();
                going_right.push_back(swapped);
                going_right.pop_front();
                left_arrivals[cows[i].pos] += (earliest_rightgoer.wt);
            }
        } else {
            going_right.push_back(cows[i]);
        }
    }

    // rightgoers
    deque<cow> going_left;
    map<i64, i64> right_arrivals;
    for (i64 i = N; i >= 1; i--) {
        if (cows[i].dir == 1) {
            i64 t = L - cows[i].pos;
            if (going_left.empty()) {
                right_arrivals[t] += (cows[i].wt);
            } else {
                cow swapped = cows[i];
                swapped.dir = -1;
                cow earliest_leftgoer = going_left.front();
                going_left.push_back(swapped);
                going_left.pop_front();
                right_arrivals[t] += (earliest_leftgoer.wt);
            }
        } else {
            going_left.push_back(cows[i]);
        }
    }

    map<i64, i64> total_arrivals;    
    for (auto p: left_arrivals) {
        total_arrivals[p.first] += p.second;
        // printf("left: %lld at %lld\n", p.second, p.first);
    }
    for (auto p: right_arrivals) {
        total_arrivals[p.first] += p.second;
        // printf("right: %lld at %lld\n", p.second, p.first);
    }

    i64 T = 0;
    i64 weight_so_far = 0;
    i64 min_needed = weight_sum / 2;
    if (weight_sum % 2 != 0) min_needed++;
    for (auto p: total_arrivals) {
        weight_so_far += p.second;
        if (weight_so_far >= min_needed) {
            T = p.first;
            break;
        }
    }

    // printf("T is %lld\n", T);
    // printf("%lld\n", T);

    // now we know the number of seconds, we just have to find number of meetings
    // we can just compute from perspective of left going right (rightgoers), to avoid duplicates
    // two pointers?

    i64 meetings = 0;
    // stores number of leftgoers within 1 to X
    vector<i64> pfx(N + 1);
    for (i64 i = 1; i <= N; i++) {
        pfx[i] = pfx[i - 1];
        if (cows[i].dir == -1) {
            pfx[i]++;
        }
    }

    // remember: 2 * T !!!! They can come back as well, so...
    i64 i = 1;
    i64 j = 1;
    while (i <= N) {
        j = max(j, i);
        if (cows[i].dir == 1) {
            i64 max_pos = cows[i].pos + 2 * T;
            while (j != N && cows[j + 1].pos <= max_pos) {
                j++;
            }
            // number of leftgoers within me to j
            meetings += pfx[j] - pfx[i - 1];
            // printf("between %lld and %lld, %lld meetings\n", i, j, pfx[j] - pfx[i - 1]);
        }
        i++;
    }

    printf("%lld\n", meetings);
}