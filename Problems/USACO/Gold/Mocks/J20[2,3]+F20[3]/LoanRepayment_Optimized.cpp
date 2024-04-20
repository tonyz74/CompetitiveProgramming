#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

i64 N, M, K;

bool check(i64 X) {
    i64 G = 0;

    for (i64 D = 1; D <= K; ) {
        i64 Y = (N - G) / X;
        Y = max(Y, M);

        // if we're already at M, we can just short circuit.
        if (Y == M) {
            // include this current day
            i64 days_left = K - D + 1;
            return days_left * M + G >= N;
        }

        i64 mod = (N - G) % X;
        i64 more_days = mod / Y + 1;    // +1 for this current day
        D += more_days;

        G += Y * more_days;
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