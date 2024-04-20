#include <iostream>
#include <vector>
#include <iomanip>
#include <ctgmath>

using namespace std;

using i64 = long long;
using f64 = double;

i64 N;
f64 L;
vector<pair<i64, i64> > towers;

f64 sq(f64 in) {
    return in * in;
}

bool contiguous(f64 R) {
    f64 rightmost = 0;

    for (int i = 0; i < N; i++) {
        f64 x = towers[i].first;
        f64 y = towers[i].second;
        f64 d = sq(2.0 * x) - 4.0 * (sq(x) + sq(y) - sq(R));

        if (d > 0) {
            f64 x1 = (2.0 * x - sqrt(d)) / 2;
            f64 x2 = (2.0 * x + sqrt(d)) / 2;

            // printf("i: %d, x1: %lf, x2: %lf\n", i, x1, x2);

            if (x1 < rightmost) {
                rightmost = max(rightmost, x2);
            }
        }
    }

    // printf("leftmost: %lf, rightmost: %lf\n", leftmost, rightmost);
    return rightmost >= L;
}

int main(void) {
    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        pair<i64, i64> p;
        cin >> p.first >> p.second;
        towers.push_back(p);
    }

    // printf("contiguous: %d\n", contiguous(7.8102));
    // return 0;

    f64 lo = 1.0;
    f64 hi = 1.5e9;

    while (hi - lo > 1e-4) {
        f64 mid = (hi + lo) / 2;

        // we want the largest value where it's not contiguous
        if (contiguous(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    cout << fixed << setprecision(4) << lo << endl;
}