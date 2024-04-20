#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

i64 get_blk_sum(
    const vector<vector<i64> >& pfx,
    pair<i64, i64> bl,
    pair<i64, i64> tr
) {
    i64 top = tr.first;
    i64 right = tr.second;
    i64 bottom = bl.first;
    i64 left = bl.second;
    return pfx[top][right] - pfx[bottom - 1][right] - pfx[top][left - 1] + pfx[bottom - 1][left - 1];
}

void solve() {
    i64 n, q; cin >> n >> q;
    vector<vector<i64> > data(1001, vector<i64>(1001, 0));

    for (int i = 1; i <= n; i++) {
        int h, w; cin >> h >> w;
        data[h][w] += h * w;
    }

    vector<vector<i64> > pfx(1001, vector<i64>(1001, 0));
    for (i64 i = 1; i <= 1000; i++) {
        for (i64 j = 1; j <= 1000; j++) {
            // x x - 0
            // | | T 0
            // 0 0 0 0
            pfx[i][j] = data[i][j] + pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= q; i++) {
        i64 hs, ws, hb, wb; cin >> hs >> ws >> hb >> wb;
        printf("%lld\n", get_blk_sum(pfx, { hs + 1, ws + 1 }, { hb - 1, wb - 1 }));
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}