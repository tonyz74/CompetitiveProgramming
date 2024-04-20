#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N, K, L; cin >> N >> K >> L;
    vector<i64> original_c(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> original_c[i];
    }
    std::sort(original_c.begin() + 1, original_c.end());
    std::reverse(original_c.begin() + 1, original_c.end());

    i64 lo = 0;
    i64 hi = N;

    auto check = [&] (i64 h) {
        if (h == 0) return true;
        
        i64 total_need = 0;

        for (i64 i = 1; i <= h; i++) {
            i64 c = original_c[i];
            if (c >= h) continue;

            i64 rem = (h - c);
            // printf("%lld: %lld, %lld\n", i, c, rem);
            if (rem > K) return false;
            // printf("rem of %lld: %lld\n", c, rem);
            total_need += rem;
        }

        return total_need <= K * L;
    };

    while (lo < hi) {
        i64 mid = (lo + hi + 1) / 2;

        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << endl;
}