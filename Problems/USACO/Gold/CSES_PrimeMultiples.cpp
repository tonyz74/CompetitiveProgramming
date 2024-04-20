#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
using i64 = long long;

bool will_overflow(i64 a, i64 b) {
    i64 max_val = INT64_MAX;

    i64 div = max_val / a;
    return div < b;
}

int main(void) {
    i64 N; cin >> N;
    i64 K; cin >> K;

    i64 ans = 0;
    vector<i64> primes(K);
    for (int i = 0; i < K; i++) {
        cin >> primes[i];
        ans += N / primes[i];
    }

    for (i64 mask = 0; mask < (1 << K); mask++) {
        i64 num = 1;
        i64 n_used = 0;
        for (i64 i = 0; i < K; i++) {
            if (mask & (1 << i)) {
                if (will_overflow(num, primes[i])) {
                    goto skip;
                }

                num *= primes[i];
                if (num > N) goto skip;

                n_used++;
            }
        }

        if (n_used >= 2) {
            if (n_used % 2 == 0) {
                ans -= N / num;
                // printf("sub %lld (%lld)\n", N / num, num);
            } else {
                ans += N / num;
                // printf("add %lld (%lld)\n", N / num, num);
            }
        }

        skip: (void) 0;
    }
    
    cout << ans << endl;
}