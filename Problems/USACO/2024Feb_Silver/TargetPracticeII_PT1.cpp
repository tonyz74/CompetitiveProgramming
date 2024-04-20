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

void solve() {
    i64 N, X1;
    cin >> N >> X1;

    i64 top = 0;
    i64 bottom = 0;

    vector<rect> rects(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> rects[i].bottom >> rects[i].top >> rects[i].right;
    }


    int all_same = true;
    i64 n_negatives = 0;
    i64 n_positives = 0;
    vector<i64> slopes(4 * N + 4);

    i64 slope_mag = 0;
    for (i64 i = 1; i <= 4 * N; i++) {
        cin >> slopes[i];
        if (slopes[i] < 0) n_negatives++;
        else if (slopes[i] > 0) n_positives++;

        if (slope_mag == 0) slope_mag = abs(slopes[i]);
        if (slope_mag != abs(slopes[i])) {
            all_same = false;
        }
    }

    for (i64 i = 1; i <= N; i++) {
        top = max(top, rects[i].right * slope_mag + rects[i].top);    
        bottom = min(bottom, rects[i].bottom - rects[i].right * slope_mag);
    }

    // won't have enough for each corner
    if (n_positives < N || n_negatives < N) {
        printf("-1\n");
    } else {
        printf("%lld\n", top - bottom);
    }

}

int main(void) {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}