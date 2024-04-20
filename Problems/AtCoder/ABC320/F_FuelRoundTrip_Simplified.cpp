#include <iostream>
#include <vector>

using namespace std;

int main(void) {

    int N, H;
    cin >> N >> H;

    vector<int> X(N);
    vector<int> F(N);
    vector<int> P(N);

    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> P[i] >> F[i];
    }

    vector<vector<int> > DP(N + 1, vector<int>(H + 1, 1e9));

    // DP[got to N][liters of fuel when reaching N][liters of fuel when leaving N].
    // result is DP[N][k][k] for any k (going back and getting there should have exactly the same).

    // there are three ways to transition: either don't use the gas, use it when going right, or use
    // it when going left. therefore three potential updates.

    for (int n = 1; n <= N; n++) {
        int dist = (X[n + 1] - X[n]);

        for (int h = 1; h <= H; h++) {
            if (dist <= h) {
                DP[n + 1][h - dist] = min(
                    DP[n + 1][h - dist],
                    DP[n][h]
                );
            }

            int new_oil = min(h + F[n], H);
            if (new_oil - dist >= 0) {
                DP[n + 1][new_oil - dist] = min(
                    // its current value
                    DP[n + 1][new_oil - dist],
                    // added oil
                    DP[n][h] + P[n]
                );
            }
        }
    }
}