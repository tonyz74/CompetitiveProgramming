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
    // gcd is exactly b for some reason
    for (i64 b = 1; b <= min(M, 500ll); b++) {
        // printf("\n[b = %lld]\n", b);
        // map<i64, vector<i64> > has_gcd;
        for (i64 a = 1; a <= N; a++) {
            if ((a + b) % (b * gcd(a, b)) == 0) {
                ans++;
                // has_gcd[gcd(a, b)].push_back(a);
            }
        }

        // if (!has_gcd.empty()) {
        //     printf("\n[b = %lld]\n", b);
        //     for (auto p: has_gcd) {
        //         printf("gcd of %lld: ", p.first);
        //         for (i64 x: p.second) {
        //             printf("%lld, ", x);
        //         }
        //         printf("\n");
        //     }
        // }
    }

    cout << ans << endl;
}

int main(void) {
    sieve();

    int T; cin >> T;
    while (T--) solve();
}
