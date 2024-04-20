#include <stdio.h>
#include <vector>

using namespace std;

int main(void) {
    int N;
    scanf("%d", &N);

    vector<int> A(N, 0);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    vector<int> sums(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        sums[i] = sums[i - 1] + A[i - 1];
    } 

    vector<vector<int> > DP(N, vector<int>(N, 0));

    for (int len = 2; len <= N; len++) {
        for (int i = 0; i < N; i++) {
            int j = i + len - 1;

            if (j < N) {
                int added = sums[j + 1] - sums[i];

                for (int k = i; k < j; k++) {
                    int a = DP[i][k];
                    int b = DP[k + 1][j];
                    DP[i][j] = max(DP[i][j], a + b + added);
                }
            }
        }
    }

    printf("%d\n", DP[0][N - 1]);
}
