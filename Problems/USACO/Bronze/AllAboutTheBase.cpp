#include <iostream>
#include <vector>
#include <cmath>

typedef long double f64;
typedef long long i64;

using namespace std;

bool is_sqr(i64 n) {
    f64 sqrt_flt = sqrt((f64) n);
    i64 sqrt_int = (i64) round(sqrt_flt);
    
    return sqrt_int * sqrt_int == n;
}

void solve() {
    int N1, N2; cin >> N1 >> N2;

    bool swapped = false;

    // enumerate over the smaller base.
    // they are the same number so whichever
    // looks smaller in base 10 has the larger base.
    if (N1 < N2) {
        std::swap(N1, N2);
        swapped = true;
    }

    // N2 is smaller than N1

    int C = N2 % 10;
    int B = (N2 / 10) % 10;
    int A = (N2 / 100) % 10;

    int F = N1 % 10;
    int E = (N1 / 10) % 10;
    int D = (N1 / 100) % 10;

    for (i64 X = 10; X <= 15000; X++) {
        i64 delta = B * B - 4 * A * (C - D * X * X - E * X - F);
        if (delta < 0 || !is_sqr(delta)) continue;

        i64 numerator = (i64) (round(sqrt(delta))) - B; 
        if (numerator % (2 * A) != 0) continue;

        i64 Y = numerator / (2 * A);
        if (Y > X) {
            if (swapped) std::swap(X, Y);
            printf("%lld %lld\n", X, Y);
            break;
        }
    }
}

int main(void) {
    freopen("whatbase.in", "r", stdin);
    freopen("whatbase.out", "w", stdout);

    int T; cin >> T;
    for (int i = 0; i < T; i++)
        solve();
}