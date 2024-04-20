#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;
using i64 = long long;

i64 N, M;
vector<i64> hands;

bool condition(i64 min_combined_hs) {
    i64 count = 0;

    for (int h = 0; h < N; h++) {
        // set h to be the left hand. how many people
        // could be the right hand of this handshake?
        i64 remaining = min_combined_hs - hands[h];
        auto it = std::lower_bound(hands.begin(), hands.end(), remaining);

        i64 n_valid = hands.end() - it;
        count += n_valid;

    }

    return count >= M;
}

int main(void) {
    cin >> N >> M;

    hands.resize(N);
    for (i64 i = 0; i < N; i++) {
        cin >> hands[i];
    }
    std::sort(hands.begin(), hands.end());

    i64 lo = 1;
    i64 hi = 1e7;

    // last true
    while (lo < hi) {
        // mid is the size of the smallest handshake pair
        // i.e. all handshakes must be at least as large as `mid`
        i64 mid = (lo + hi + 1) / 2;

        if (condition(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    vector<i64> pfx(N, 0);
    pfx[0] = hands[0];
    for (int i = 1; i < N; i++) {
        pfx[i] = pfx[i - 1] + hands[i];
    }

    i64 count = 0;
    i64 ans = 0;

    for (int left = 0; left < N; left++) {
        i64 remain = lo - hands[left];
        auto it = std::lower_bound(hands.begin(), hands.end(), remain);

        if (it != hands.end()) {
            i64 it_pos = it - hands.begin();
            i64 n_valid = hands.end() - it;

            ans += n_valid * hands[left];
            ans += pfx[N - 1] - ((it_pos == 0) ? 0 : pfx[it_pos - 1]);
            count += n_valid;
        }
    }

    ans -= (count - M) * lo;
    printf("%lld\n", ans);
}