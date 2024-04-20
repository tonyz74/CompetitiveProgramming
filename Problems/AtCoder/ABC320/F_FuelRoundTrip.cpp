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

    vector<vector<vector<int> > > DP(
        N + 1, vector<vector<int> >(H + 1, vector<int>(H + 1, 1e9))
    );

    // DP[got to N][liters of fuel when reaching N][liters of fuel when leaving N].
    // result is DP[N][k][k] for any k (going back and getting there should have exactly the same).

    // there are three ways to transition: either don't use the gas, use it when going right, or use
    // it when going left. therefore three potential updates.

    for (int n = 1; n <= N; n++) {
        int dist = (X[n + 1] - X[n]);

        for (int h_forward = 1; h_forward <= H; h_forward++) {
            for (int h_backward = 1; h_backward <= H; h_backward++) {

                if (dist <= h_forward) {
                    DP[n + 1][h_forward - dist][h_backward] = min(
                        DP[n + 1][h_forward - dist][h_backward],
                        DP[n][h_forward][h_backward]
                    );
                }

                int new_oil_fwd = min(h_forward + F[n], H);
                if (new_oil_fwd - dist >= 0) {
                    DP[n + 1][new_oil_fwd - dist][h_backward] = min(
                        DP[n + 1][new_oil_fwd - dist][h_backward],
                        DP[n][h_forward][h_backward] + P[n]
                    );
                }
                
            }
        }
    }
}