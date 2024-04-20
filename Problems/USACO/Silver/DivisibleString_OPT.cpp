#include <iostream>
#include <vector>
#include <string>
#include <bit>

using namespace std;
using i64 = long long;

vector<int> read_da() {
    string S; cin >> S;
    vector<int> v;
    for (char c: S) v.push_back(c - '0');
    return v;
}

#define MAX_N 10
#define MAX_D 1000

i64 dp[1 << MAX_N][MAX_D];

int main(void) {
    i64 N, D; cin >> N >> D;
    vector<int> S = read_da();

    dp[0][0] = 1;

    for (i64 mask = 0; mask < (1 << N); mask++) {
        for (i64 mod = 0; mod < D; mod++) {

            for (i64 to_take = 0; to_take < N; to_take++) {
                if ((mask & (1 << to_take)) == 0) {
                    dp[mask | (1 << to_take)][((mod * 10) + S[to_take]) % D] += dp[mask][mod];
                }

            }

        }
    }

    i64 ans = dp[(1 << N) - 1][0];
    cout << ans << endl;
}