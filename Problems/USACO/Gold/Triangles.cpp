#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

using i64 = long long;

const i64 MODULUS = 1e9 + 7;

struct point {
    i64 x, y;
    int id;

    bool operator<(const point& rhs) {
        return make_pair(x, y) < make_pair(rhs.x, rhs.y);
    }
};

vector<i64> calc_differences(const vector<pair<i64, int> >& in) {
    vector<i64> output(in.size());
    i64 n_values = in.size();

    i64 curr_value = 0;
    for (int i = 0; i < n_values; i++) {
        curr_value += abs(in[0].first - in[i].first);
        curr_value %= MODULUS;
    }

    output[0] = curr_value;

    // currently at the ith position
    for (i64 i = 0; i < n_values - 1; i++) {
        i64 n_below = i + 1;
        i64 n_above = n_values - n_below;

        i64 diff_next = in[i + 1].first - in[i].first;
        curr_value += n_below * diff_next;
        curr_value -= n_above * diff_next;
        curr_value %= MODULUS;

        output[i + 1] = curr_value;
    }

    return output;
}

int main(void) {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    i64 N; cin >> N;
    vector<point> cows(N);

    vector<int> idx_x(N + 1);
    vector<int> idx_y(N + 1);

    map<i64, vector<pair<i64, int> > > same_x;
    map<i64, vector<pair<i64, int> > > same_y;

    map<i64, vector<i64> > height_diffs;
    map<i64, vector<i64> > width_diffs;

    for (i64 i = 0; i < N; i++) {
        cin >> cows[i].x >> cows[i].y;
        cows[i].id = i;
    }

    for (i64 i = 0; i < N; i++) {
        same_x[cows[i].x].push_back(make_pair(cows[i].y, cows[i].id));
        same_y[cows[i].y].push_back(make_pair(cows[i].x, cows[i].id));
    }

    for (auto p: same_x) {
        std::sort(p.second.begin(), p.second.end());

        for (int i = 0; i < (int) p.second.size(); i++) {
            idx_y[p.second[i].second] = i;
        }

        height_diffs[p.first] = calc_differences(p.second);
    }
    for (auto p: same_y) {
        std::sort(p.second.begin(), p.second.end());

        for (int i = 0; i < (int) p.second.size(); i++) {
            idx_x[p.second[i].second] = i;
        }

        width_diffs[p.first] = calc_differences(p.second);
    }

    i64 area = 0;
    // printf("safe here\n");

    // assume cow i is the corner
    for (int i = 0; i < N; i++) {
        i64 all_heights = height_diffs[cows[i].x][idx_y[i]];
        i64 all_widths = width_diffs[cows[i].y][idx_x[i]];

        area += (all_heights * all_widths);
        area %= MODULUS;
    }

    cout << area << endl;
}