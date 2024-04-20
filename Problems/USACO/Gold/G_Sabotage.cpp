#include <iostream>
#include <vector>
#include <ios>
#include <iomanip>

using namespace std;
using i64 = long long;
using f64 = double;

i64 N;
vector<f64> M;

f64 max_subarray_sum(const vector<f64>& prefix, int n) {
    f64 ans = -1e9;
    f64 best_pre = 1e9;

    for (int i = 1; i <= n; i++) {
        f64 sub = (i == 1) ? 0 : best_pre;
        ans = max(ans, prefix[i] - sub);
        best_pre = min(best_pre, prefix[i]);
    }

    return ans;
}

bool check(double shift) {
    vector<f64> prefix(N + 1);
    for (i64 i = 1; i <= N; i++) {
        prefix[i] = prefix[i - 1] + M[i] - shift;
    }
    f64 total_sum = prefix[N];

    vector<f64> accessible(1, 0);
    for (i64 i = 2; i <= N - 1; i++) {
        accessible.push_back(prefix[i] - prefix[1]);
    }
    f64 max_sum = max_subarray_sum(accessible, N - 2);
    return total_sum - max_sum >= 0;
}

int main(void) {
    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);

    cin >> N;
    M.resize(N + 1);
    for (int i = 1; i <= N; i++) cin >> M[i];

    f64 lo = 0.0;
    f64 hi = 1e8;

    // find last true
    while ((hi - lo) >= 0.0001) {
        double mid = (lo + hi) / 2;
        int res = check(mid);
        if (res) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    cout << setprecision(3) << fixed;
    cout << lo << endl;
}