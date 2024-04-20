#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

// i, j, mask
// i => ends at time i
// j => currently at time j
// mask => ending state of lights
// 
// assuming we make no further modifications to the switches
// after this point, can we reach mask in time j?
//
// to actually check validity we just check for all i=j.
//
// we do this in reverse, starting from mask = 0

int main(void) {
    int N, T; cin >> T >> N;

    vector<vector<int> > dp(64, vector<int>(1 << N, 0));
    vector<vector<int> > reachable(64, vector<int>(1 << N, 0));

    for (int i = 0; i <= 3 * N; i++) {
        dp[0][0] = true;

        for (int j = 0; j <= i; j++) {
            for (int mask = 0; mask < (1 << N); mask++) {

                int time_til_end = i - j;
                for (int pos = 0; pos < N; pos++) {
                    int new_mask = mask;

                    int counter = time_til_end;
                    int xor_pos = pos;
                    while (counter) {
                        xor_pos++;
                        xor_pos %= N;
                        new_mask ^= (1 << xor_pos);
                        counter--;
                    }

                    dp[j + 1][new_mask] = max(dp[j + 1][new_mask], dp[j][mask]);
                }

            }
        }

        for (int mask = 0; mask < (1 << N); mask++) {
            if (dp[i][mask]) {
                reachable[i][mask] = true;
            }
        }
    }
}