#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

void solve() {
    i64 n; cin >> n;
    vector<i64> a(n + 1);
    vector<i64> b(n + 1);

    for (i64 i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (i64 i = 1; i <= n; i++) {
        cin >> b[i];
    }

    auto get_ans = [&] (i64 i) {
        if (i == 0) return 0ll;

        i64 a_sum = 0, b_sum = 0;

        vector<i64> a_now(i + 1);
        vector<i64> b_now(i + 1);

        for (i64 j = 1; j <= i; j++) {
            a_now[j] = a[j];
            a_sum += a[j];
        }

        for (i64 j = 1; j <= i; j++) {
            b_now[j] = b[j];
            b_sum += b[j];
        }

        std::sort(a_now.begin() + 1, a_now.end());
        std::sort(b_now.begin() + 1, b_now.end());

        vector<bool> is_gt(i + 2);
        vector<i64> bad(1);
        is_gt[i + 1] = true;
        for (i64 j = 1; j <= i; j++) {
            is_gt[j] = b_now[j] > a_now[j - 1];
            if (is_gt[j]) {
                bad.push_back(j);
            }
        }
        bad.push_back(i + 1);

        i64 best = 4e18;
        for (i64 x = 1; x < (i64) bad.size() - 1; x++) {
            // printf("%lld %lld\n", bad[x], bad[x + 1]);
            best = min(best, (a_sum - a_now[bad[x + 1] - 1]) - (b_sum - b_now[bad[x]]));
        }

        return best;
    };

    for (i64 subarray = 1; subarray <= n; subarray++) {
        cout << get_ans(subarray) << " ";
    }
    cout << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}