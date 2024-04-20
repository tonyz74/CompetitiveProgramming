#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int N, M; cin >> N >> M;
    vector<int> A(N + 1, 0); for (int i = 1; i <= N; i++) cin >> A[i];

    sort(A.begin(), A.end());

    int best = 0;

    // for (int i = 1; i <= N; i++) printf("%d ", A[i]);
    // printf("\n");

    int end = 1;
    for (int start = 1; start <= N; start++) {
        // printf("must exceed %d (end is %d)\n", A[start] + M, end);
        while (end <= N && A[end] < A[start] + M) {
            // printf("OK: A[%d] = %d\n", end, A[end]);
            end++;
        }

        // printf("starting at %d, got %d (end is %d)\n", start, end - start, end);
        best = max(best, end - start);
    }

    printf("%d\n", best);
}