#include <iostream>
#include <vector>

using namespace std;

const int MOD = 19650827;

// important: you can add another dimension to just
// add a bit more information (who did we come from)
// as long as its a really low amount (2 choices)
int DP[1001][1001][2];

int main(void) {
    int N; cin >> N;
    vector<int> H(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> H[i];
    }

    for (int i = 1; i <= N; i++) {
        // assume we can only put the first one at the right
        // most element of the array
        DP[i][i][1] = 1;
    }

    for (int len = 1; len <= N; len++) {
        for (int i = 1; i + len - 1 <= N; i++) {
            int j = i + len - 1;

            int left = i - 1;
            if (left >= 1) {
                if (H[i] > H[left]) {
                    DP[left][j][0] += DP[i][j][0];
                    DP[left][j][0] %= MOD;
                }

                if (H[j] > H[left]) {
                    DP[left][j][0] += DP[i][j][1];
                    DP[left][j][0] %= MOD;
                }
            }

            int right = j + 1;
            if (right <= N) {
                if (H[right] > H[i]) {
                    DP[i][right][1] += DP[i][j][0];
                    DP[i][right][1] %= MOD;
                }

                if (H[right] > H[j]) {
                    DP[i][right][1] += DP[i][j][1];
                    DP[i][right][1] %= MOD;
                }
            }
        }
    }

    cout << ((DP[1][N][0] + DP[1][N][1]) % MOD) << endl;
}