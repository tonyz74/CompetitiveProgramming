#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <tuple>

using namespace std;
using i64 = long long;

struct point {
    int ty;
    i64 x, y;
    i64 count;

    bool operator<(const point& rhs) const {
        return y < rhs.y;
    }
};
using ms = multiset<point>;

int main(void) {
    i64 N; cin >> N;
    vector<point> saved_in(N);

    for (int i = 0; i < N; i++) {
        i64 t, x;
        cin >> saved_in[i].ty >> t >> x >> saved_in[i].count;
        saved_in[i].x = x - t;
        saved_in[i].y = x + t;
    }

    sort(saved_in.begin(), saved_in.end(), [] (auto lhs, auto rhs) {
        if (lhs.x != rhs.x) {
            return lhs.x > rhs.x;
        }
        return lhs.y < rhs.y;
    });

    ms cows;
    i64 taken = 0;

    for (int i = 0; i < N; i++) {
        if (saved_in[i].ty == 1) {
            cows.insert(saved_in[i]);
        } else {
            // find cow with highest y that is to my right,
            // so upper bound - 1
            i64 n_left = saved_in[i].count;

            while (n_left != 0) {
                auto it = cows.upper_bound(saved_in[i]);
                if (it == cows.begin()) break;
                it--;

                i64 take = min(it->count, n_left);
                point save = *it;
                save.count -= take;
                n_left -= take;
                taken += take;

                cows.erase(it);

                if (save.count != 0) cows.insert(save);
            }
        }
    }

    cout << taken << endl;
}