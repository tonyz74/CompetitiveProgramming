#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <cassert>

using namespace std;

using i64 = long long;

// i64 dp[800][800];
i64 parities[800][800];

int main(void) {
    i64 N; cin >> N;

    for (i64 i = 0; i < 800; i++) {
        for (i64 j = 0; j < 800; j++) {
            parities[i][j] = -1;
        }
    }

    map<i64, vector<i64> > direct_conns;
    i64 n_direct = 0;

    for (i64 i = 1; i <= N; i++) {
        string S; cin >> S;

        i64 cnt = 0;
        for (i64 j = i + 1; j <= N; j++) {
            parities[i][j] = S[cnt] - '0';
            cnt++;

            if (j == i + 1 && parities[i][j] == 1) {
                direct_conns[i].push_back(j);
                // printf("init: %d with %d\n", i, j);
                n_direct++;
            }
        }
    }


    // initial state

    // for (i64 i = 1; i <= N - 1; i++) {
    //     if (parities[i][i + 1] == 1) {
    //         dp[i][i + 1] = 1;
    //     }
    // }

    for (i64 len = 3; len <= N; len++) {
        for (i64 i = 1; i <= N; i++) {
            i64 sum = 0;
            i64 j = i + len - 1;

            if (j > N) break;

            for (i64 conn: direct_conns[i]) {
                // sum += dp[conn][j];
                sum += parities[conn][j];
            }

            // assert(sum <= 1e18);
            // we need to add a direct connection to fix,
            // as the parities are incorrect right now
            if (sum % 2 != parities[i][j]) {
                direct_conns[i].push_back(j);
                n_direct++;
                // dp[i][j] = sum + 1;
            } else {
                // dp[i][j] = sum;
            }
        }
    }

    // for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= N; j++) {
    //         printf("%d ", dp[i][j]);
    //     }
    //     printf("\n");
    // }

    cout << n_direct << endl;
}