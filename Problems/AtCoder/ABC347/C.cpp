#include <iostream>
#include <vector>
#include <algorithm>

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

    i64 mn = 1e10, mx = 0;

    for (i64 i = 1; i <= N; i++) {
        mn = min(mn, M[i]);
        mx = max(mx, M[i]);
    }
    if (mx - mn + 1 <= A) {
        printf("Yes\n");
        return 0;
    }

    // printf("mx, mn: %lld, %lld\n", mx, mn);
    std::sort(M.begin() + 1, M.end());
    for (int brk = 1; brk <= N - 1; brk++) {
        int rhs = brk + 1;
        i64 dist = (M[brk] + 1) + (A + B - M[rhs]);

        if (dist <= A) {
            printf("Yes\n");
            return 0;
        }
    }

    printf("No\n");
}