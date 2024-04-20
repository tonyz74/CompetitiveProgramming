#include <iostream>
#include <vector>
#include <bitset>
#include <string>

using namespace std;
using i64 = long long;

using bs = bitset<48>;

vector<int> to_digits(i64 value) {
    if (value == 0) return {0};

    string val_str = bs(value).to_string();
    vector<int> output;

    bool is_lead_zero = true;
    for (char c: val_str) {
        if (c == '0' && is_lead_zero) continue;
        is_lead_zero = false;
        output.push_back(c - '0');
    }

    return output;
}

// DP[pos][diff between 0s and 1s][started][less than]

i64 n_round_numbers(vector<int> max_val) {
    // do digit dp in binary
    i64 dp[32][64][2][2];
    for (int x = 0; x < 32; x++) for (int diff = 0; diff < 64; diff++) {
        for (int s = 0; s < 2; s++) for (int lt = 0; lt < 2; lt++) {
            dp[x][diff][s][lt] = 0;
        }
    }

    // put the 0 at the first location (must be smaller)
    // actual difference in 1s and 0s didn't shift because it was
    // just a leading 0, which has no importance in calculation
    dp[0][32][0][1] = 1;

    // put the 1 at the first location (must have started)
    dp[0][31][1][0] = 1;

    // fix iteration order
    for (int x = 0; x < (int) max_val.size() - 1; x++) for (int diff = 0; diff < 64; diff++) {
        for (int s = 0; s < 2; s++) for (int lt = 0; lt < 2; lt++) {
            if (dp[x][diff][s][lt] == 0) continue;

            int max_digit = (lt) ? 1 : max_val[x + 1];

            for (int i = 0; i <= max_digit; i++) {
                int next_s = s | (i != 0);
                int next_lt = lt | (i < max_digit); 

                int next_diff = diff;
                if (s == 1 && i == 0) next_diff++;
                else if (i == 1) next_diff--;

                if (next_diff < 0 || next_diff > 63) continue;

                // printf("dp[%d][%d][%d][%d](now %lld) add to dp[%d][%d][%d][%d](now %lld) (give %d)\n",
                //     x, diff, s, lt, dp[x][diff][s][lt], x + 1,
                //     next_diff, next_s, next_lt, dp[x + 1][next_diff][next_s][next_lt],
                //     i
                // );

                dp[x + 1][next_diff][next_s][next_lt] += dp[x][diff][s][lt];
            }

        }

        // printf("\n");
    }

    i64 answer = 0;
    for (int diff = 32; diff < 63; diff++) {
        answer += dp[max_val.size() - 1][diff][1][0];
        answer += dp[max_val.size() - 1][diff][1][1];
    }
    
    return answer;
}

int main(void) {
    i64 L, R;
    cin >> L >> R;

    auto upper = to_digits(R);
    auto lower = to_digits(L - 1);
    // for (int i: upper) cout << i << " ";
    // cout << endl;
    cout << n_round_numbers(upper) - n_round_numbers(lower) << endl;
}