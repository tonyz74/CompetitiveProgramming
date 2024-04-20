#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using i64 = long long;

struct line_info {
    i64 write_time = 0;
    i64 color = 0;

    line_info() {}
    line_info(i64 wt, i64 cl): write_time(wt), color(cl) {
    }

    bool operator<(const line_info& rhs) const {
        return make_pair(write_time, color) < make_pair(rhs.write_time, rhs.color);
    }
};

int main(void) {
    i64 H, W; cin >> H >> W;
    i64 M; cin >> M;

    vector<line_info> row_upd(H + 1);
    vector<line_info> col_upd(W + 1);

    for (i64 i = 1; i <= H; i++) {
        row_upd[i].write_time = -i;
        row_upd[i].color = 0;
    }

    for (i64 i = 1; i <= W; i++) {
        // distinguish between all times
        col_upd[i].write_time = -i - H - 1;
        col_upd[i].color = 0;
    }

    for (i64 i = 1; i <= M; i++) {
        i64 T, A, X; cin >> T >> A >> X;

        // update some row
        if (T == 1) {
            row_upd[A].write_time = i;
            row_upd[A].color = X;
        } else if (T == 2) {
            col_upd[A].write_time = i;
            col_upd[A].color = X;
        }
    }

    std::sort(row_upd.begin() + 1, row_upd.end());
    std::sort(col_upd.begin() + 1, col_upd.end());

    vector<i64> row_diff_arr(H + 4);
    vector<i64> col_diff_arr(W + 4);

    map<i64, i64> colors;

    // for (i64 i = 1; i <= H; i++) {
    //     printf("row upd %lld: %lld, %lld\n", i, row_upd[i].write_time, row_upd[i].color);
    // }

    // for (i64 i = 1; i <= W; i++) {
    //     printf("col upd %lld: %lld, %lld\n", i, col_upd[i].write_time, col_upd[i].color);
    // }

    // printf("\n");

    for (i64 row = 1; row <= H; row++) {
        i64 time = row_upd[row].write_time;
        i64 ub = std::upper_bound(col_upd.begin(), col_upd.end(), line_info(time, 1e9)) - col_upd.begin();

        colors[row_upd[row].color] += W;
        
        // printf("%lld: time %lld, color %lld, ub = %lld\n", row, row_upd[row].write_time, row_upd[row].color, ub);

        // find first value that has greater time
        if (ub == 0) continue;
        col_diff_arr[1]++;
        col_diff_arr[ub]--;
    }

    for (i64 col = 1; col <= W; col++) {
        i64 time = col_upd[col].write_time;
        i64 ub = std::upper_bound(row_upd.begin(), row_upd.end(), line_info(time, 1e9)) - row_upd.begin();

        colors[col_upd[col].color] += H;

        if (ub == 0) continue;
        row_diff_arr[1]++;
        row_diff_arr[ub]--;
    }

    i64 mark = 0;
    for (i64 i = 1; i <= H + 3; i++) {
        mark += row_diff_arr[i];
        colors[row_upd[i].color] -= mark;
    }

    mark = 0;
    for (i64 i = 1; i <= W + 3; i++) {
        mark += col_diff_arr[i];
        colors[col_upd[i].color] -= mark;
    }

    i64 nonzero = 0;
    for (auto p: colors) {
        if (p.second != 0) nonzero++;
    }

    cout << nonzero << endl;
    for (auto p: colors) {
        if (p.second != 0) {
            cout << p.first << " " << p.second << endl;
        }
    }
}
