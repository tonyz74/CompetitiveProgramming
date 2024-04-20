#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>

using namespace std;
using i64 = long long;

struct monster {
    i64 pos = 0;
    i64 damage_in = 0;
};

void solve() {
    i64 n; cin >> n;
    vector<i64> atk(n + 2);
    vector<i64> def(n + 2);

    for (i64 i = 1; i <= n; i++) cin >> atk[i];
    for (i64 i = 1; i <= n; i++) cin >> def[i];

    set<i64> alive;
    alive.insert(0); alive.insert(n + 1);

    vector<monster> M(n + 1);
    vector<i64> deaths;

    for (i64 i = 1; i <= n; i++) {
        alive.insert(i);
        M[i].pos = i;
        M[i].damage_in = atk[i - 1] + atk[i + 1];
        if (M[i].damage_in > def[i]) {
            deaths.push_back(i);
        }
    }

    for (i64 time = 1; time <= n; time++) {
        i64 died_this_round = 0;
        set<i64> to_refresh;

        // do all removals together
        for (i64 x: deaths) {
            auto fnd = alive.find(x);
            auto lhs = fnd; lhs--;
            auto rhs = fnd; rhs++;

            if (*lhs != 0) to_refresh.insert(*lhs);
            if (*rhs != n + 1) to_refresh.insert(*rhs);

            alive.erase(fnd);
            died_this_round++;
        }

        printf("%lld ", died_this_round);

        deaths.clear();

        for (i64 x: to_refresh) {
            auto fnd = alive.find(x);
            if (fnd == alive.end()) continue;

            auto left = fnd; left--;
            auto right = fnd; right++;

            if (def[*fnd] < atk[*left] + atk[*right]) {
                deaths.push_back(*fnd);
            }
        }
    }
    printf("\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}