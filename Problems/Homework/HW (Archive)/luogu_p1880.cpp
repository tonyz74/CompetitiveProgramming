#include <stdio.h>
#include <vector>
#include <limits.h>

using namespace std;

int main(void) {
    int N;
    scanf("%d", &N);

    vector<int> A(N * 2, 0);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[N + i] = A[i];
    }

    int original_N = N;
    N *= 2;

    vector<int> sums(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        sums[i] = sums[i - 1] + A[i - 1];
    } 

    vector<vector<int> > MAX(N, vector<int>(N, 0));
    vector<vector<int> > MIN(N, vector<int>(N, INT_MAX));

    for (int i = 0; i < N; i++) {
        MIN[i][i] = 0;
    }

    for (int len = 2; len <= N; len++) {
        for (int i = 0; i < N; i++) {
            int j = i + len - 1;

            if (j < N) {
                int added = sums[j + 1] - sums[i];

                for (int k = i; k < j; k++) {
                    int a = MAX[i][k];
                    int b = MAX[k + 1][j];
                    MAX[i][j] = max(MAX[i][j], a + b + added);

                    int c = MIN[i][k];
                    int d = MIN[k + 1][j];
                    MIN[i][j] = min(MIN[i][j], c + d + added);
                }
            }
        }
    }

    int max_val = 0;
    int min_val = INT_MAX;
    for (int i = 0; i < N - (original_N - 1); i++) {
        max_val = max(max_val, MAX[i][i + original_N - 1]);
        min_val = min(min_val, MIN[i][i + original_N - 1]);
    }

    printf("%d\n%d\n", min_val, max_val);
}

