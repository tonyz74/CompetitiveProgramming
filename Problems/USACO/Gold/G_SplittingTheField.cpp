#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

using i64 = long long;

struct point { i64 x, y; };

template<typename T>
point set_back(const T& s) {
    auto back = s.end();
    back--;
    return *back;
}

template<typename T, typename U>
i64 get_area(const T& x_set, const U& y_set) {
    if (x_set.empty() || y_set.empty()) return 0;

    i64 left = x_set.begin()->x;
    i64 right = set_back(x_set).x;

    i64 top = y_set.begin()->y; 
    i64 bottom = set_back(y_set).y;

    return (bottom - top) * (right - left);
}

int main(void) {
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);

    i64 N; cin >> N;
    vector<point> P(N);

    for (i64 i = 0; i < N; i++) {
        cin >> P[i].x >> P[i].y;
    }

    const auto cmp_x = [] (const auto& lhs, const auto& rhs) {
        return make_pair(lhs.x, lhs.y) < make_pair(rhs.x, rhs.y);
    };
    const auto cmp_y = [] (const auto& lhs, const auto& rhs) {
        return make_pair(lhs.y, lhs.x) < make_pair(rhs.y, rhs.x);
    };

    set<point, decltype(cmp_x)> by_x_save(cmp_x);
    set<point, decltype(cmp_y)> by_y_save(cmp_y);

    for (point p: P) {
        by_x_save.insert(p);
        by_y_save.insert(p);
    }

    i64 original_area = get_area(by_x_save, by_y_save);
    i64 min_area = 1e18;

    // first try a horizontal line to split
    {
        set<point, decltype(cmp_x)> x_above = by_x_save;
        set<point, decltype(cmp_x)> x_below(cmp_x);
        set<point, decltype(cmp_y)> y_above = by_y_save;
        set<point, decltype(cmp_y)> y_below(cmp_y);

        // placing a horizontal split line at points[hsplit]
        // placing it behind the very last one would have
        // no purpose at all...
        auto cit = by_y_save.cbegin();
        for (i64 hsplit = 0; hsplit < N; hsplit++) {
            x_below.insert(*cit);
            y_below.insert(*cit);
            y_above.erase(*cit);
            x_above.erase(*cit);

            auto after = cit;
            after++;

            if (after == by_y_save.cend() || after->y != cit->y) {
                i64 above_area = get_area(x_above, y_above);
                i64 below_area = get_area(x_below, y_below);
                min_area = min(min_area, above_area + below_area);
            }

            cit++;
        }
    }

    // then try splitting a vertical line
    {
        set<point, decltype(cmp_x)> x_right = by_x_save;
        set<point, decltype(cmp_x)> x_left(cmp_x);
        set<point, decltype(cmp_y)> y_right = by_y_save;
        set<point, decltype(cmp_y)> y_left(cmp_y);

        // placing a horizontal split line at points[hsplit]
        // placing it behind the very last one would have
        // no purpose at all...
        auto cit = by_x_save.cbegin();
        for (i64 hsplit = 0; hsplit < N; hsplit++) {
            x_left.insert(*cit);
            y_left.insert(*cit);
            y_right.erase(*cit);
            x_right.erase(*cit);

            auto after = cit;
            after++;

            if (after == by_x_save.cend() || after->x != cit->x) {
                i64 left_area = get_area(x_left, y_left);
                i64 right_area = get_area(x_right, y_right);
                min_area = min(min_area, left_area + right_area);
            }

            cit++;
        }
    }

    cout << original_area - min_area << endl;
}