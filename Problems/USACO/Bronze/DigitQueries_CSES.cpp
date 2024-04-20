#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

i64 pows_10[24];

void solve() {
    i64 k; cin >> k;
    i64 digits = 1;
    i64 prev_max_val = 0;
    i64 prev_csum = 0;
    i64 csum = 9;

    while (csum < k) {
        digits++;
        prev_csum = csum;
        prev_max_val += pows_10[digits - 2] * 9;
        csum += pows_10[digits - 1] * digits * 9;
    }

    i64 spare = k - prev_csum;
    i64 div = spare / digits;

    if (spare % digits != 0) {
        div++;
    }

    i64 actual = prev_max_val + div;

    i64 depth_from_left = spare % digits;
    if (depth_from_left == 0) depth_from_left = digits;

    i64 state = actual;
    vector<int> decomposition = {};
    while (state != 0) {
        decomposition.push_back(state % 10);
        state /= 10;
    }
    reverse(decomposition.begin(), decomposition.end());

    printf("%d\n", decomposition[depth_from_left - 1]);
}

int main(void) {
    i64 p10 = 1;
    for (int i = 0; i < 24; i++) {
        pows_10[i] = p10;
        p10 *= 10;
    }

    i64 q; cin >> q;
    for (int i = 0; i < q; i++) {
        solve();
    }
}