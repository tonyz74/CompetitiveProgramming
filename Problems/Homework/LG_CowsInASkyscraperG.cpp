#include <iostream>
#include <vector>

using namespace std;

const int INF = 2e9;
#define MAX_MASK ((int) (2<<19))

// min weight on the current elevator to get max mask on there

// we don't actually need this N
int dp[20][MAX_MASK];
int C[20];

int main(void) {
    for (int i = 0; i <= 18; i++) {
        for (int mask = 0; mask < MAX_MASK; mask++) {
            dp[i][mask] = INF;
        }
    }

    int N; cin >> N;
    int W; cin >> W; 

    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }

    dp[0][0] = W;

    for (int E = 0; E <= N; E++) {
        for (int mask = 0; mask < (1 << N); mask++) {
            if (dp[E][mask] > W) continue;

            for (int cow = 0; cow < N; cow++) {
                // skip if already set
                if ((mask & (1 << cow))) continue;

                int new_mask = mask | (1 << cow);
                dp[E + 1][new_mask] = min(dp[E + 1][new_mask], C[cow]);
                
                if (dp[E][mask] + C[cow] <= W) {
                    dp[E][new_mask] = min(dp[E][new_mask], dp[E][mask] + C[cow]);
                }
            }
        }
    }

    // for (i64 E = 0; E <= N; E++) {
    //     printf("E = %lld: ", E);
    //     for (i64 mask = 0; mask < (1 << N); mask++) {
    //         printf("%s: ", bitset<4>(mask).to_string().c_str());
    //         if (dp[E][mask] > W) {
    //             printf("-1");
    //         } else {
    //             printf("%2lld", dp[E][mask]);
    //         }
    //         printf(" ");
    //     }
    //     printf("\n");
    // }

    for (int E = 0; E <= N; E++) {
        if (dp[E][(1 << N) - 1] <= W) {
            printf("%d\n", E);
            return 0;
        }
    }
}