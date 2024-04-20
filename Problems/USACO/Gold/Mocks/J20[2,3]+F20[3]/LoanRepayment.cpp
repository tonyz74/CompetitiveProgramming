#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

i64 N, M, K;

bool check(i64 X) {
    i64 G = 0;

    for (i64 D = 1; D <= K; D++) {
        i64 Y = (N - G) / X;
        Y = max(Y, M);
        printf("day %lld: already gave %lld, Y was %lld, set to %lld\n", D, G, (N - G) / X, Y);

        G += Y;
        if (G >= N) {
            return true;
        }
    }

    return false;
}

int main(void) {
    freopen("loan.in", "r", stdin);
    freopen("loan.out", "w", stdout);

    cin >> N >> K >> M;

    i64 lo = 1;
    i64 hi = N; // we can do this because M * K < N

    // find last true
    while (lo < hi) {
        i64 mid = (lo + hi + 1) / 2;
        // printf("\n\nchecking %lld:\n", mid);
        int res = check(mid);

        if (res) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    printf("%lld\n", lo);
}