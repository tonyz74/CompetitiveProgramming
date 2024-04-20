#include <iostream>
#include <vector>
#include <string>

using namespace std;

using i64 = long long;

#define int long long

int original[1024][1024];
int spun[2048][2048];

i64 pre_sum[2048][2048];

signed main(void) {
    freopen("lazy.in", "r", stdin);
    freopen("lazy.out", "w", stdout);

    int N; cin >> N;
    int K; cin >> K;

    for (int i = 0; i < 2048; i++) for (int j = 0; j < 2048; j++)
        spun[i][j] = -1;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> original[i][j];
            spun[i + j][N - i + j] = original[i][j];
        }
    }


    // for (int i = 0; i <= 14; i++) {
    //     for (int j = 0; j <= 14; j++) {
    //         printf("%3d ", state[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    for (int i = 1; i < 2048; i++) {
        for (int j = 1; j < 2048; j++) {
            int val = max(spun[i][j], 0ll);
            pre_sum[i][j] += val + pre_sum[i-1][j] + pre_sum[i][j-1] - pre_sum[i-1][j-1];
        }
    }

    i64 best_ans = 0;
    // for (int row = 1; row <= 14; row++) {
    //     for (int col = 1; col <= 14; col++) {
    //         printf("%3lld ", pre_sum[row][col]);
    //     }
    //     printf("\n");
    // }

    // a b c d
    // e f g h
    // i j k l
    // m n o p

    for (int row = 1; row <= 2 * N; row++) {
        for (int col = 1; col <= 2 * N; col++) {
            if (spun[row][col] == -1) continue;

            i64 value = pre_sum[row + K][col + K];
             
            if (col - K - 1 >= 0) {
                value -= pre_sum[row + K][col - K - 1];
            }

            if (row - K - 1 >= 0) {
                value -= pre_sum[row - K - 1][col + K];
            }

            if (row - K - 1 >= 0 && col - K - 1 >= 0) {
                value += pre_sum[row - K - 1][col - K - 1];
            }
    
            // printf("%lld + %lld - %lld - %lld\n", pre_sum[top - 1][left - 1], pre_sum[bottom][right], pre_sum[right][top - 1], pre_sum[left - 1][bottom]);

            best_ans = max(best_ans, value);
        }
    }

    cout << best_ans << endl;
}