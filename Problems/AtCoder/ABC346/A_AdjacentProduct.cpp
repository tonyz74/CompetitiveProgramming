#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N; cin >> N;
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for (int i = 1; i < N; i++) {
        printf("%d", A[i] * A[i + 1]);
        if (i != N - 1) printf(" ");
    }
    printf("\n");
}