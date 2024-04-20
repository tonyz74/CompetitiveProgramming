#include <iostream>
#include <vector>

// first optimization: prefix sum optimization

using namespace std;
const int MOD = 1e9 + 7;

int N, K;

void solve_slow() {
    vector<vector<int> > DP(N + 4, vector<int>(K + 4, 0));
    DP[0][0] = 1;

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            for (int k = 0; k <= i; k++) {
                DP[i + 1][j + k] += DP[i][j];
                DP[i + 1][j + k] %= MOD;
            }
        }
    }

    printf("%d\n", (MOD + DP[N][K]) % MOD);
}

void solve_fast() {
    vector<vector<int> > DP(N + 4, vector<int>(K + 4, 0));
    DP[0][0] = 1;

    for (int i = 1; i <= N; i++) {
        vector<int> prefix_sum(K + 4, 0);
        prefix_sum[0] = DP[i - 1][0];
        for (int j = 1; j <= K; j++) {
            prefix_sum[j] = prefix_sum[j - 1] + DP[i - 1][j];
            prefix_sum[j] %= MOD;
        }

        for (int j = 0; j <= K; j++) {
            int min_val = max(0, j - (i - 1));
            int to_sub = (min_val != 0) ? prefix_sum[min_val - 1] : 0;
            DP[i][j] += prefix_sum[j] - to_sub;
            DP[i][j] %= MOD;
        }
    }

    printf("%d\n", (MOD + DP[N][K]) % MOD);
}

int main(void) {
    cin >> N >> K;
    solve_fast();
}