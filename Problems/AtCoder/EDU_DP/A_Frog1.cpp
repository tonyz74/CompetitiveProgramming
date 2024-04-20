#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N; cin >> N;
    vector<i64> H(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> H[i];
    }

    vector<i64> DP(N + 5, 1e18);
    DP[1] = 0;
    for (i64 i = 1; i <= N; i++) {
        DP[i + 1] = min(DP[i + 1], DP[i] + abs(H[i + 1] - H[i]));
        DP[i + 2] = min(DP[i + 2], DP[i] + abs(H[i + 2] - H[i]));
    }

    cout << DP[N] << endl;
}