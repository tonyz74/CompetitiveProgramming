#include <iostream>
#include <string>
#include <vector>

using namespace std;
using i64 = long long;

// We can condense information into a single state by having all answers for all left
// positions given a right position

i64 N;
string S;
vector<vector<int>> chr_best_prev;

i64 get_closest_prev_bessie(i64 pos) {
    vector<char> req = {'e', 'i', 's', 's', 'e', 'b'};
    i64 i = pos;
    for (char jmp: req) {
        // nobody before with this one
        if (i <= 0 || chr_best_prev[i][jmp - 'a'] == -1) {
            return -1;
        }

        i = chr_best_prev[i][jmp - 'a'] - 1;
    }

    // returns index of the 'b'
    return i + 1;
}

int main(void) {
    cin >> S;
    S = "." + S;
    N = S.size() - 1;

    chr_best_prev.resize(N + 1, vector<int>(26, -1));

    vector<int> current(26, -1);
    for (int i = 1; i <= N; i++) {
        current[S[i] - 'a'] = i;
        chr_best_prev[i] = current;
    }

    i64 sum = 0;
    // DP[i] has i fixed at the right, sum of all ans with any as left start
    vector<i64> dp(N + 1);
    for (i64 i = 1; i <= N; i++) {
        i64 prev_b = get_closest_prev_bessie(i);
        if (prev_b == -1) continue;
        // +1 for the single "bessie" case
        dp[i] = dp[prev_b - 1] + (prev_b - 1) + 1;
        sum += dp[i];
    }

    cout << sum << endl;
}