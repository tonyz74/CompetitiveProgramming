#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <ctgmath>

using namespace std;

typedef long double llf;

// dp[k][i] -> taking k items, considered the first i items
llf dp[5004][5004];

int main(void) {
    int N; cin >> N;
    vector<int> P(N + 1);
    for (int i = 1; i <= N; i++) cin >> P[i];

    // If we fix the number of contests we do, the
    // only thing that actually changes is the top part
    // of the left side of R.

    for (int k = 1; k <= N; k++) {
        for (int i = k; i <= N; i++) {
            dp[k][i] = max(dp[k - 1][i - 1] * 0.9 + P[i], dp[k][i - 1]);
        }
    }

    // for (int k = 0; k <= N; k++) {
    //     for (int i = 0; i <= N; i++) {
    //         printf("%Lf ", dp[k][i]);
    //     }
    //     printf("\n");
    // }

    llf best = -INFINITY;
    llf cmult = 0.9L;

    for (int k = 1; k <= N; k++) {
        llf denom = 10 * (1 - cmult);
        best = max(best, dp[k][N] / denom - (1200.0L / sqrtl((llf) k)));
        cmult *= 0.9L;
    }

    cout << setprecision(8);
    cout << best << endl;
}