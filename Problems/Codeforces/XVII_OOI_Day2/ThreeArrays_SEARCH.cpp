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

    if (N <= 5000) {
        vector<i64> suffix(N + 2);
        for (i64 i = N; i >= 1; i--) {
            suffix[i] = suffix[i + 1] + D[i];
        }

        auto value_at = [&] (i64 should_be) {
            // who is B not allowed to use min on?

            // if we just can't do it even if we never min b, just fail
            if (b0 + suffix[1] < should_be) return -(i64) (1e14 + 5 + should_be - suffix[1] - b0);

            vector<bool> B_can_pick(N + 1);

            for (i64 i = 1; i <= N; i++) {
                if (R[i] + suffix[i + 1] >= should_be) {
                    B_can_pick[i] = true;
                }
            }

            i64 max_final_a = a0 + suffix[1];
            for (i64 i = 1; i <= N; i++) {
                // final_a must be lteq req
                i64 req = L[i] + suffix[i + 1];
                if (B_can_pick[i] == false) {
                    max_final_a = min(max_final_a, req);
                }
            }

            i64 a = a0;
            i64 b = b0;
            for (i64 i = 1; i <= N; i++) {
                a += D[i];
                b += D[i];
 
                if (L[i] + suffix[i + 1] >= max_final_a) {
                    a = min(a, L[i]);
                } else {
                    b = min(b, R[i]);
                }
            }
 
            return a + b;
        };

        i64 prev_ans = 0;
        i64 ans = 0;
        for (i64 i = 0; i <= b0 + suffix[1]; i++) {
            i64 now = value_at(i);
            if (now != prev_ans) {
                printf("%lld (%lld) ; ", now, i);
            }
            prev_ans = now;
            ans = max(ans, value_at(i));
        }
        cout << endl;
        cout << ans << endl;
        return 0;
    } else {
        cout << 0 << endl;
    }
}