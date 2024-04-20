#include <iostream>
#include <vector>
#include <tgmath.h>
#include <cmath>

using namespace std;

using f64 = double;
using i64 = long long;

struct frac {
    i64 numer;
    i64 denom;

    frac(i64 n, i64 d) {
        numer = n;
        denom = d;
    }

    bool operator<=(const frac& rhs) const {
        return (numer * rhs.denom) <= (rhs.numer * denom);
    }

    bool operator<(const frac& rhs) const {
        return (numer * rhs.denom) < (rhs.numer * denom);
    }
};

frac f(i64 n, i64 h, i64 c, i64 t) {
    return frac(abs((n + 1) * h + n * c - (2 * n + 1) * t), 2 * n + 1);
}

void solve() {
    i64 h, c, t; cin >> h >> c >> t;

    i64 odd_n = -1;

    // odd number of pours
    if (2 * t - h - c != 0) {
        i64 ix = (h - t) / (2 * t - h - c);
        // printf("ix: %lld\n", ix);

        if (ix >= 0 || (h - t) == 0) {
            i64 b = ix;
            i64 a = ix + 1;
            
            frac lhs = f(b, h, c, t);
            frac rhs = f(a, h, c, t);

            // printf("lhs: %lld / %lld\n", lhs.numer, lhs.denom);
            // printf("rhs: %lld / %lld\n", rhs.numer, rhs.denom);

            if (lhs <= rhs) {
                odd_n = b;
            } else {
                odd_n = a;
            }
        }
    }

    i64 n = odd_n;
    if (n == -1 || frac(abs(h + c - 2 * t), 2) < f(n, h, c, t)) {
        printf("2\n");
    } else {
        printf("%lld\n", 2 * n + 1);
    }
}

int main(void) {
    int t; cin >> t;
    for (int i = 0; i < t; i++) solve();
}