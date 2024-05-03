#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

// dp[i][curr_sum][lt/eq]
i64 dp[55][55][2];

int main(void) {
    i64 N; cin >> N;
    i64 N_orig = N;

    i64 length = 0;
    for (length = 50; length >= 0; length--) {
        if (N & (1ll << length)) {
            break;
        }
    }
    length++;

    vector<int> digits;
    while (N > 0) {
        digits.push_back(N % 2);
        N >>= 1;
    }
    std::reverse(digits.begin(), digits.end());
    
    // initially empty, we have not put anything yet
    // comparing with the empty one of our maximum answer, it's equal
    dp[0][0][1] = 1;

    for (i64 i = 0; i < length; i++) {
        for (i64 curr_sum = 0; curr_sum <= length; curr_sum++) {

            for (i64 to_put = 0; to_put <= 1; to_put++) {
                if (to_put < digits[i]) {

                    dp[i + 1][curr_sum + to_put][0] += dp[i][curr_sum][0];    
                    dp[i + 1][curr_sum + to_put][0] += dp[i][curr_sum][1];    

                } else if (to_put == digits[i]) {

                    dp[i + 1][curr_sum + to_put][0] += dp[i][curr_sum][0];
                    dp[i + 1][curr_sum + to_put][1] += dp[i][curr_sum][1];

                } else {
                    
                    dp[i + 1][curr_sum + to_put][0] += dp[i][curr_sum][0];

                }
            }

        }
    }

    i64 ans = 1;
    for (i64 sum = 1; sum <= 54; sum++) {
        i64 both = dp[length][sum][0] + dp[length][sum][1];

        // should become fastpow
        i64 val = 1;
        for (i64 i = 0; i < both; i++) {
            val *= sum; 
            val %= (i64) (1e9 + 7);
        }

        ans *= val;
        ans %= (i64) (1e9 + 7);
    }

    unsigned long long mult = 1;
    for (unsigned long long i = 1; i <= (unsigned long long) N_orig; i++) {
        mult *= __builtin_popcountll(i);
        mult %= (i64) (1e9 + 7);
    }

    assert(mult == (unsigned long long) ans);
    cout << ans << endl;
}