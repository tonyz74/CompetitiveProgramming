#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long i64;

void solve() {
    i64 N; cin >> N;
    vector<i64> A(N);
    for (i64 i = 0; i < N; i++) cin >> A[i];

    i64 min_x = 0;
    i64 max_x = 1e9;

    for (i64 i = 0; i < N - 1; i++) {
        // update min and max for this pair

        if (A[i] < A[i + 1]) {
            max_x = min(max_x, ((i64) (A[i] + A[i+1])) / 2);
        } else if (A[i] > A[i + 1]) {
            i64 numer = (A[i] + A[i+1]);
            i64 res = numer / 2;

            // ceil
            if (numer % 2 == 1) {
                res++;
            }

            min_x = max(min_x, res);
        }
    }

    if (max_x < min_x) {
        printf("-1\n");
    } else {
        printf("%lld\n", min_x);
    }
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
}