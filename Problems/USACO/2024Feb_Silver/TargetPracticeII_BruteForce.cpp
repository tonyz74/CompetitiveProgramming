#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using i64 = long long;

struct rect {
    i64 top = 0;
    i64 bottom = 0;
    i64 right = 0;
};

struct vtx {
    i64 x = 0;
    i64 y = 0;

    vtx() {}
    vtx(i64 xc, i64 yc): x(xc), y(yc) {}
};

bool cmp_tr(vtx tr1, vtx tr2) {
    // we want big right x to come first
    return make_pair(tr1.y + tr1.x, -tr1.x) < make_pair(tr2.y + tr2.x, -tr2.x);
}

bool cmp_br(vtx br1, vtx br2) {
    return make_pair(br1.y - br1.x, -br1.x) < make_pair(br2.y - br2.x, -br2.x);
}

void solve() {
    i64 N, X1;
    cin >> N >> X1;

    vector<rect> rects(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> rects[i].bottom >> rects[i].top >> rects[i].right;
    }

    vector<i64> slopes(4 * N + 4);
    for (i64 i = 1; i <= 4 * N; i++) {
        cin >> slopes[i];
    }

    i64 N_cows = 0;

    for (i64 i = 1; i <= 4 * N; i++) {

    }

}

int main(void) {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}