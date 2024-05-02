#include <iostream>
#include <vector>
#include <numeric>
#include <bitset>
#include <map>

using namespace std;
using i64 = long long;

#define MAX_VAL (i64(2 * (1e6) + 7))

// 1 means it's not a prime
bitset<MAX_VAL> check;

void sieve() {
    check[0] = 1;
    check[1] = 1;
    for (int i = 2; i < MAX_VAL; i++) {
        if (check[i] == 0) {
            for (int j = 1; i * j < MAX_VAL; j++) {
                check[i * j] = 1;
            }
            check[i] = 0;
        }
    }
}

void solve() {
    i64 N, M; cin >> N >> M;

    i64 ans = 0;
    for (i64 b = 1; b <= M; b++) {
        // gcd is exactly b for some reason
        i64 gcd_value = b;

        // find all a such that a + b mod b^2 = 0
        i64 mod_base = b * gcd_value;
        i64 congruent_to = mod_base - b;

        // 1 to N, 0 not included
        i64 blocks = N / mod_base;
        i64 contrib = blocks;

        if (congruent_to == 0) {
            contrib--;
        }

        if (N % mod_base == congruent_to) {
            contrib++;
        }

        i64 ext = N - blocks * mod_base;
        if (ext - 1 >= congruent_to) {
            contrib++;
        }

        // if (contrib != 0) {
        //     printf("%lld => %lld (wanted %lld under %lld)\n", b, contrib, congruent_to, mod_base);
        // }

        ans += contrib;
    }

    cout << ans << endl;
}

int main(void) {
    sieve();

    int T; cin >> T;
    while (T--) solve();
}
