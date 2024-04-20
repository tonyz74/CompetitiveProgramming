#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using i64 = long long;

i64 solve(const vector<i64>& heights) {
    i64 ans = 0;
    i64 N = heights.size();

    // left to right pass
    for (i64 i = 0; i < N; i++) {
        i64 loc = -1;
        for (i64 j = i; j < N; j++) {
            if (heights[j] > heights[i]) {
                loc = j;
                break;
            }
        }

        if (loc != -1) {
            // printf("%lld and %lld (%lld)\n", heights[i], heights[loc], loc - i + 1);
            ans += loc - i + 1;
        }
    }

    return ans;
}

int main(void) {
    // i64 ans = 0;
    i64 N; cin >> N;
    vector<i64> H(N);
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }

    i64 ans = solve(H);

    // std::reverse(H.begin(), H.end());
    // ans += solve(H);

    cout << ans << endl;
}