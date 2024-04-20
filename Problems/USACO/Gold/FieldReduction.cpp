#include <iostream>
#include <set>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

struct point {
    int x, y;

    point() {}
    point(int h, int v): x(h), y(v) {}
};

typedef long long i64;

#define SMALL 1
#define LARGE 2

vector<pair<int, int> > to_use {
    {0, 3},
    {3, 0},
    {1, 2},
    {2, 1}
};

vector<array<int, 3> > removal;

void gen_perms() {
    vector<int> state = {SMALL, SMALL, SMALL, LARGE, LARGE, LARGE};

    do {
        removal.push_back({state[0], state[1], state[2]});
        reverse(state.begin() + 3, state.end());
    } while (next_permutation(state.begin(), state.end()));
}

template<typename C>
point val_at_pos(const set<point, C>& S, int pos) {
    if (pos == SMALL) {
        return *S.begin();
    } else if (pos == LARGE) {
        return *S.rbegin();
    } else {
        printf("ERROR!\n");
        exit(-1);
    }
}

int main(void) {
    freopen("reduce.in", "r", stdin);
    freopen("reduce.out", "w", stdout);

    gen_perms();

    int N; cin >> N;

    auto cmp_x = [] (const point& lhs, const point& rhs) {
        return make_pair(lhs.x, lhs.y) < make_pair(rhs.x, rhs.y);
    };
    set<point, decltype(cmp_x)> sorted_x(cmp_x);

    auto cmp_y = [] (const point& lhs, const point& rhs) {
        return make_pair(lhs.y, lhs.x) < make_pair(rhs.y, rhs.x);
    };
    set<point, decltype(cmp_y)> sorted_y(cmp_y);

    i64 min_area = 1e18;

    for (int i = 0; i < N; i++) {
        int x, y; cin >> x >> y;
        sorted_x.insert(point(x, y));
        sorted_y.insert(point(x, y));
    }

    for (const auto& rem_x: removal) {
        for (const auto& rem_y: removal) {
            for (auto &&[use_x, use_y]: to_use) {
                vector<point> removed;
                removed.reserve(4);

                // remove the stuff specified in removal
                for (int i = 0; i < use_x; i++) {
                    point vx = val_at_pos(sorted_x, rem_x[i]);
                    sorted_x.erase(vx);
                    sorted_y.erase(vx);

                    removed.push_back(vx);
                }

                for (int i = 0; i < use_y; i++) {
                    point vy = val_at_pos(sorted_y, rem_y[i]);
                    sorted_x.erase(vy);
                    sorted_y.erase(vy);

                    removed.push_back(vy);
                }

                // calculate area
                i64 big_y = sorted_y.rbegin()->y;
                i64 small_y = sorted_y.begin()->y;

                i64 big_x = sorted_x.rbegin()->x;
                i64 small_x = sorted_x.begin()->x;

                min_area = min(min_area, (big_y - small_y) * (big_x - small_x));

                for (int i = 0; i < (int) removed.size(); i++) {
                    sorted_x.insert(removed[i]);
                    sorted_y.insert(removed[i]);
                }
            }
        }
    }

    cout << min_area << endl;
}

