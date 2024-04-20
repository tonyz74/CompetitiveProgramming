#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N, A, B; cin >> N >> A >> B;
    vector<i64> D(N + 1);
    vector<i64> M(N + 1);

    for (i64 i = 1; i <= N; i++) {
        cin >> D[i];
        M[i] = D[i] % (A + B);
    }

    for (i64 shift = 0; shift <= A; shift++) {
        bool all_ok = true;

        for (i64 i = 1; i <= N; i++) {
            if (A + shift > M[i] && M[i] >= shift) {
                // printf("%lld\n", M[i]);
            } else {
                all_ok = false;
                break;
            }
        }

        if (all_ok) {
            // printf("Yes %lld\n", shift);
            printf("Yes\n");
            return 0;
        }
    }

    printf("No\n");
}