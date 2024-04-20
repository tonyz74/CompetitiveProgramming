#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N, K; cin >> N >> K;
    vector<i64> H(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> H[i];
    }

    vector<i64> DP(N + 5, 1e18);
    DP[1] = 0;

    for (i64 i = 1; i <= N; i++) {
        for (i64 k = 1; k <= K; k++) {
            if (i + k > N) break;
            DP[i + k] = min(DP[i + k], DP[i] + abs(H[i + k] - H[i]));
        }
    }

    cout << DP[N] << endl;
}