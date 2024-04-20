#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int dp[502][502];
vector<char> match;

int main(void) {
    match.resize(255, 0);
    match[(int) '('] = ')';
    match[(int) '['] = ']';

    int N; cin >> N;
    string S; cin >> S;

    // other range dp iteration style:
    // i => N - 1 -> 0 (down)
    // j => i + 1 -> N (up)

    // although isn't in global order, every subsequence
    // will have all its smaller subsequences computed
    // by the time it itself is reached

    for (int len = 2; len <= N; len++) {
        for (int left = 0; left < N; left++) {
            int right = left + len - 1;
            if (right >= N) continue;

            dp[left][right] = max(dp[left][right], dp[left + 1][right]);
            dp[left][right] = max(dp[left][right], dp[left][right - 1]);

            // add surrounding brackets
            if (match[(int) S[left]] && match[(int) S[left]] == S[right]) {
                dp[left][right] = max(dp[left][right], dp[left + 1][right - 1] + 2);
            }

            for (int midpoint = left + 1; midpoint <= right - 1; midpoint++) {
                dp[left][right] = max(dp[left][right], dp[left][midpoint] + dp[midpoint + 1][right]);
            }
        }
    }

    cout << dp[0][N - 1] << endl;
}