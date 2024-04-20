#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N, L, R; cin >> N >> L >> R;
    vector<int> A(N + 1, 0); for (int i = 1; i <= N; i++) cin >> A[i];

    for (int i = 1; i <= N; i++) {
        if (i != 1) printf(" ");

        if (L <= A[i] && R >= A[i]) {
            printf("%d", A[i]);
        } else if (A[i] < L) {
            printf("%d", L);
        } else if (A[i] > R) {
            printf("%d", R);
        } else {
            printf("no clue\n");
        }
    }

    printf("\n");
}