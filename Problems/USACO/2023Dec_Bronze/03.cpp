#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

struct plant_info {
    i64 initial;
    i64 rate;

    bool operator<(const plant_info& rhs) const {
        return make_pair(rate, initial) < make_pair(rhs.rate, rhs.initial);
    }
};

i64 solve() {
    int N; cin >> N;

    // sort by desired ordering
    vector<i64> orig_initial(N);
    vector<pair<i64, plant_info> > plants(N);

    for (int i = 0; i < N; i++) {
        cin >> plants[i].second.initial;
        orig_initial[i] = plants[i].second.initial;
    }
    for (int i = 0; i < N; i++)
        cin >> plants[i].second.rate;
    for (int i = 0; i < N; i++)
        cin >> plants[i].first;

    sort(plants.begin(), plants.end());

    // do a 0 check first
    for (int i = 0; i < N; i++) {
        if (plants[i].first != i) return -1;
    }

    // for (int i = 0; i < N; i++) {
    //     printf("%lld + %lldx > ", plants[i].second.initial, plants[i].second.rate);
    // }
    // printf("\n");

    // 0 is actually a valid min_x
    i64 bound_min_x = -1;
    i64 bound_max_x = 1e18;

    for (int i = 0; i < N - 1; i++) {
        // solve for x in plants[i] > plants[i + 1]
        i64 x_coeff = plants[i].second.rate - plants[i + 1].second.rate;
        i64 rhs = plants[i + 1].second.initial - plants[i].second.initial;

        // (r1 - r2) x > (b2 - b1)

        if (x_coeff == 0) {
            // 0 > (b2 - b1)
            // (b2 - b1) < 0
            if (rhs >= 0) return -1;
        } else if (x_coeff > 0) {
            // x > (b2 - b1) / (r1 - r2)
            i64 value = rhs / x_coeff;

            // rounding down is fine, as we're taking > anyways
            if ((rhs > 0 && x_coeff < 0) || (rhs < 0 && x_coeff > 0)) {
                // result will be negative, val > -0.01 is val >= 0
                value = -1;
            }

            bound_min_x = max(bound_min_x, value);
        } else if (x_coeff < 0) {
            // must round up now
            i64 value = rhs / x_coeff;
            if (abs(rhs) % abs(x_coeff) != 0) {
                value++;
            }

            bound_max_x = min(bound_max_x, value);
        }

        // printf("%lld %lld\n", bound_min_x, bound_max_x);
    }

    if (bound_max_x >= bound_min_x + 2) {
        return bound_min_x + 1;
    } else {
        return -1;
    }
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        i64 res = solve();
        printf("%lld\n", res);
    }
}