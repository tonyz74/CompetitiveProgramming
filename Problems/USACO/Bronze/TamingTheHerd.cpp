#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);

    int N; cin >> N;
    vector<int> A(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    A[0] = 0;

    for (int i = 0; i < N; i++) {
        // if a log reads x, we can count backwards
        // until x reaches 0

        if (A[i] >= 1) {
            int x = A[i] - 1;
            for (int j = i - 1; j >= 0 && x >= 0; j--) {
                // will have been filled in previously
                if (A[j] != -1 && A[j] != x) {
                    printf("-1\n");
                    return 0;
                }

                A[j] = x--;
            }
        }

    }

    int natural_breakouts = 0;
    int unknowns = 0;

    for (int i = 0; i < N; i++) {
        if (A[i] == 0) natural_breakouts++;
        if (A[i] == -1) unknowns++;
    }

    printf("%d %d\n", natural_breakouts, natural_breakouts + unknowns);
}