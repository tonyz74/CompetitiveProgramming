#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

void solve() {
    i64 N, K; cin >> N >> K;

    i64 sum_A = 0;
    i64 min_A = 1e18;
    vector<i64> A(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> A[i];
        sum_A += A[i];
        min_A = min(min_A, A[i]);
    }

    // max value that they can all reach
    i64 lo = min_A;
    i64 hi = (sum_A + K) / N + 5;

    auto check = [&] (i64 all_target) {
        i64 accum_cost = 0;
        for (i64 i = 1; i <= N; i++) {
            if (all_target <= A[i]) continue;
            accum_cost += all_target - A[i];
            if (accum_cost > K) return false;
        }

        return true;
    };

    while (lo < hi) {
        i64 mid = (lo + hi + 1) / 2;

        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    // will get all to lo
    i64 base = lo;

    for (i64 i = 1; i <= N; i++) {
        if (A[i] >= base) continue;

        K -= base - A[i];
        A[i] = base;
    }

    i64 ans = 0;
    ans = base * N - (N - 1);

    // and now for the extras
    vector<pair<i64, i64> > perm(N + 1);
    for (i64 i = 1; i <= N; i++) {
        // printf("%lld ", A[i]);
        perm[i].first = A[i] - base;
        perm[i].second = i;
    }
    // printf("\n");

    std::sort(perm.begin() + 1, perm.end());
    std::reverse(perm.begin() + 1, perm.end());

    i64 extended = 0;
    for (i64 i = 1; i <= N; i++) {
        if (perm[i].first == 0) {
            if (K == 0) break;
            K--;
            perm[i].first = 1;
        }

        extended = i;
    }

    ans += extended;

    cout << ans << endl;
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}
