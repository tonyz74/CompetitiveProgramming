#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N; cin >> N;
    vector<i64> D(N + 1);
    vector<i64> L(N + 1);
    vector<i64> R(N + 1);

    for (i64 i = 1; i <= N; i++) {
        cin >> D[i];
    }

    for (i64 i = 1; i <= N; i++) cin >> L[i];
    for (i64 i = 1; i <= N; i++) cin >> R[i];

    i64 a0, b0; cin >> a0 >> b0;

    if (N <= 15) {
        function<i64(i64, i64, i64)> dfs = [&] (i64 i, i64 a, i64 b) {
            if (i == N + 1) {
                // printf("returning %lld (a, b = %lld %lld)\n", a + b, a, b);
                return a + b;
            }

            a += D[i];
            b += D[i];

            i64 opt1 = dfs(i + 1, min(a, L[i]), b);
            i64 opt2 = dfs(i + 1, a, min(b, R[i]));
            return max(opt1, opt2);
        };

        cout << dfs(1, a0, b0) << endl;
    }
}