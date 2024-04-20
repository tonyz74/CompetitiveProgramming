#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

using namespace std;

vector<bool> dp;

struct edge {
    int s, e;
    int t;

    bool operator==(const edge& rhs) const {
        return s == rhs.s && e == rhs.e && t == rhs.t;
    }

    bool operator<(const edge& rhs) const {
        return vector<int>({s, e, t}) < vector<int>({rhs.s, rhs.e, rhs.t});
    }
};

struct hasher {
    size_t operator()(const edge& p) const {
        std::hash<int> int_hasher;
        return (unsigned long) (int_hasher(p.s) ^ int_hasher(p.e) ^ int_hasher(p.t));
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t; cin >> n >> t;
    dp.resize(n + 1, 0);

    // starting point to all edges starting from there
    vector<unordered_set<edge, hasher> > unused_edges(n + 1);

    // currently walkable (and not deleted) edges, mapped from time
    vector<vector<edge> > walkable_edges(t + 1);

    for (int i = 1; i <= t; i++) {
        int m; cin >> m;
        for (int j = 1; j <= m; j++) {
            int u, v; cin >> u >> v;
            unused_edges[u].insert({ .s = u, .e = v, .t = i });
            unused_edges[v].insert({ .s = v, .e = u, .t = i });
        }
    }

    auto transfer = [&] (int ep) {
        vector<edge> rm_unused;

        for (edge ed: unused_edges[ep]) {
            walkable_edges[ed.t].push_back(ed);
            rm_unused.push_back(ed);
        }

        for (auto x: rm_unused) {
            unused_edges[x.s].erase(x);
        }
    };

    transfer(1);

    int k; cin >> k;
    vector<int> order(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> order[i];
    }

    dp[1] = 1;
    int jumps = 1;
    for (int kk = 1; kk <= k; kk++) {
        int time = order[kk];

        // printf("jump #%d: time %d\n", jumps, time);
        unordered_set<int> new_starts;

        for (edge ed: walkable_edges[time]) {
            // printf("%d %d\n", ed.s, ed.e);
            // we start at some place with cost to reach dp[start]

            dp[ed.e] = 1;
            // all edges that start from ed are now walkable as well
            new_starts.insert(ed.e);
        }

        // printf("size: %d %d\n", (int) rm_walkable.size(), (int) walkable_edges[time].size());
        walkable_edges[time].clear();
        // for (auto x: rm_walkable) {
            // printf("%d\n", x.t);
        //     walkable_edges[x.t].erase(x);
        // }

        for (int x: new_starts) {
            transfer(x);
        }

        // for (int i = 1; i <= n; i++) {
        //     printf("i: %d => %d\n", i, dp[i]);
        // }
        // printf("\n");

        if (dp[n] != 0) break;

        jumps++;
    }

    if (dp[n] == 0) {
        cout << -1 << endl;
    } else {
        cout << jumps << endl;
    }
}