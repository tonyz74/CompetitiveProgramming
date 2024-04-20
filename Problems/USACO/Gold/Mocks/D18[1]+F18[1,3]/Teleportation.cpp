#include <iostream>
#include <vector>
#include <map>

using namespace std;
using i64 = long long;

i64 N;

int main(void) {
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);

    cin >> N;
    i64 value = 0;
    map<i64, i64> slope_changes;

    for (int i = 1; i <= N; i++) {
        i64 a, b; cin >> a >> b;
        i64 orig_dist = abs(a - b);
        i64 k = orig_dist - abs(a);

        value += orig_dist;
        if (k < 0) {
            // printf("%lld is constant\n", orig_dist);
        } else {
            i64 low = k + b;
            i64 high = b - k;
            i64 midp = (low + high) / 2;

            slope_changes[low] += -1;
            slope_changes[midp] += 2;
            slope_changes[high] += -1;

            // printf("not constant, up: %lld, down: %lld\n", k + b, b - k);
        }
    }

    i64 ans = value;

    i64 curr_slope = 0;
    i64 prev_pos = -1e9;
    for (auto p: slope_changes) {
        i64 pos_now = p.first;
        i64 pos_diff = pos_now - prev_pos;
        value += pos_diff * curr_slope;

        curr_slope += p.second;

        prev_pos = pos_now;

        ans = min(ans, value);
        // printf("%lld => %lld\n", p.first, p.second);
    }

    // printf("%lld, %lld, %lld\n", value, ans, curr_slope);
    printf("%lld\n", ans);
}