#include <stdio.h>
#include <vector>

#define MOD_CONSTANT (1000000 + 7)

using namespace std;

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);

    vector<int> A(N, 0);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    vector<vector<int> > max_combos(N + 1, vector<int>(M + 1, 0));

    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < M + 1; j++) {
            max_combos[i][j] = max_combos[i - 1][j];

            // A starts from 0, so - 1
            int look_from = j - min(j, A[i - 1]);

            for (int k = look_from; k < j; k++) {
                if (k == 0) {
                    max_combos[i][j] += 1;
                } else {
                    max_combos[i][j] += max_combos[i - 1][k];
                }

                max_combos[i][j] %= MOD_CONSTANT;
            }
        }
    }

    // printf("results:\n");
    // for (int i = 0; i < N + 1; i++) {
    //     for (int j = 0; j < M + 1; j++) {
    //         printf("%10d ", max_combos[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("%d\n", max_combos[N][M]);
}
