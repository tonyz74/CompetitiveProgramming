#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using i64 = long long;

struct dept {
    i64 a, b;

    bool operator<(const dept& rhs) const {
        return make_pair(a, b) < make_pair(rhs.a, rhs.b);
    }
};

void solve() {
    int n; cin >> n;
    vector<dept> depts(n);

    for (int i = 0; i < n; i++) {
        cin >> depts[i].a >> depts[i].b;
    }

    std::sort(depts.begin(), depts.end());

    vector<i64> sfx_max(n);
    for (int i = n - 1; i >= 0; i--) {
        if (i != n - 1) {
            sfx_max[i] = sfx_max[i + 1];
        }
        sfx_max[i] = max(sfx_max[i], depts[i].b);
    }

    i64 min_diff = 1e18;

    multiset<i64> before;
    for (int i = 0; i < n; i++) {
        vector<i64> trial;

        if (i != n - 1 && depts[i].a == depts[i + 1].a) {
            before.insert(depts[i].b);
            trial.push_back(depts[i].b);
            i++;
        }

        trial.insert(trial.begin(), depts[i].b);
        before.insert(depts[i].b);

        i64 max_b = 0;
        if (i != n - 1) {
            max_b = sfx_max[i + 1];
            min_diff = min(min_diff, abs(max_b - depts[i].a));
        }

        // this "trial" business is to handle elements with the same depts[i].a,
        // in this case we add all their corresponding b values into a vector,
        // then try each case (removing the corresponding b, then putting it back in).

        // this code can also handle solitary elements as it'll just be one trial.

        for (i64 t: trial) {
            before.erase(before.find(t));

            // if i'm already less than max b, adding any more would just
            // increase the difference even more, so we only need to
            // pick the best option from before if there's room for
            // improving max_b to be closer to our chosen a value

            if (depts[i].a >= max_b && !before.empty()) {
                auto lb = before.lower_bound(depts[i].a);

                if (lb == before.end()) {
                    // no point looking even before, as we're already the one
                    // behind, so going even further back is just worse
                    lb--;
                } else {
                    // only if lb is in some place in the middle of the set
                    // should we even consider looking to some value smaller
                    // than depts[i].a. this value must also be greater than
                    // the current max_b for it to even work.

                    auto pre_lb = lb;
                    if (lb != before.begin()) pre_lb--;

                    // there's only a point in doing this if pre_lb
                    // can actually change the maximum for b
                    if (*pre_lb > max_b) {
                        min_diff = min(min_diff, abs(depts[i].a - *pre_lb));
                    }
                }

                // choose just lb, and nobody else from B stores
                min_diff = min(min_diff, abs(*lb - depts[i].a));
            }

            before.insert(t);
        }

        // printf("i = %d, min_diff = %lld\n", i, min_diff);
    }

    cout << min_diff << endl;
}

int main(void) {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        solve();
    }
}