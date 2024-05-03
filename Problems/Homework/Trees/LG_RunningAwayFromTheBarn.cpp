#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
using i64 = long long;

#define MAX_N ((int) (2 * 1e5 + 3))

i64 N, K;
i64 weights[MAX_N];
i64 parents[MAX_N];
i64 dist_to_root[MAX_N];
vector<i64> children[MAX_N];

using si = multiset<i64>;
si dp[MAX_N];

i64 ans[MAX_N];

void dfs(i64 current, i64 curr_dist) {
    dist_to_root[current] = curr_dist;

    for (i64 x: children[current]) {
        dfs(x, curr_dist + weights[x]);
    } 
}

void solve(i64 node) {
    i64 max_child = -1;

    for (i64 x: children[node]) {
        solve(x);

        if (max_child == -1 || dp[max_child].size() < dp[x].size()) {
            max_child = x;
        }
    }

    i64 max_wt = dist_to_root[node] + K;

    // merge
    if (max_child != -1) {
        std::swap(dp[max_child], dp[node]);
        dp[node].insert(dist_to_root[node]);

        vector<i64> to_erase;
        for (auto i = dp[node].rbegin(); i != dp[node].rend(); i++) {
            if (*i > max_wt) {
                to_erase.push_back(*i);
            } else {
                break;
            }
        }
        for (i64 x: to_erase) {
            dp[node].erase(x);
        }
    }

    for (i64 x: children[node]) {
        // insert everything insertable
        if (x != max_child) {
            for (i64 i: dp[x]) {
                if (i <= max_wt) {
                    dp[node].insert(i);
                } else {
                    break;
                }
            }
        }
    }

    ans[node] = dp[node].size();
    // printf("%lld: ", node);
    // for (i64 x: dp[node]) {
    //     printf("%lld ", x);
    // }
    // printf("\n");
}

int main(void) {
    cin >> N >> K;

    for (i64 i = 2; i <= N; i++) {
        i64 parent; cin >> parent;
        i64 wt; cin >> wt;
        weights[i] = wt;
        parents[i] = parent;
        children[parent].push_back(i);
    }

    dfs(1, 0);
    for (i64 i = 1; i <= N; i++) {
        dp[i].insert(dist_to_root[i]);
    }

    solve(1);
    for (i64 i = 1; i <= N; i++) {
        printf("%lld\n", ans[i]);
    }
}