#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct path {
    int u, v, weight;

    int lca;
    unordered_set<int> nodes;
};

void solve() {
    int n, m; cin >> n >> m;

    vector<int> parent(n + 1, 0);
    vector<int> depths(n + 1, 0);
    vector<vector<int> > tree(n + 1, vector<int>());

    vector<path> paths(m + 1);

    for (int i = 1; i <= n - 1; i++) {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    std::function<void(int, int, int)> find_depths = [&] (int now, int from, int d) {
        parent[now] = from;
        depths[now] = d;
        for (int conn: tree[now]) {
            if (conn == from) continue;
            find_depths(conn, now, d + 1);
        }
    };
    find_depths(1, 0, 0);

    // go up until same depth
    auto get_lca = [&] (int u, int v) {
        unordered_set<int> total_visited;
        total_visited.insert(v);
        total_visited.insert(u);

        while (depths[v] > depths[u]) {
            v = parent[v];
            total_visited.insert(v);
        }

        while (u != v) {
            u = parent[u];
            v = parent[v];

            total_visited.insert(v);
            if (u != v) total_visited.insert(u);
        }

        return make_pair(u, total_visited);
    };

    vector<vector<int> > paths_with_lca(n + 1, vector<int>());

    for (int i = 1; i <= m; i++) {
        cin >> paths[i].u >> paths[i].v >> paths[i].weight;
        // u must have smaller depth
        if (depths[paths[i].u] > depths[paths[i].v]) {
            std::swap(paths[i].u, paths[i].v);
        }
        auto res = get_lca(paths[i].u, paths[i].v);
        paths[i].lca = res.first;
        paths[i].nodes = res.second;

        paths_with_lca[paths[i].lca].push_back(i);
    }

    vector<int> dp(n + 1);
    std::function<void(int, int)> dfs = [&] (int now, int from) {
        // just children
        int opt_1 = 0;

        for (int child: tree[now]) {
            if (child == from) continue;
            dfs(child, now);
            opt_1 += dp[child];
        }

        // children of paths with me as lca
        int opt_2 = 0;
        for (int path_id: paths_with_lca[now]) {
            int accum = paths[path_id].weight;
            for (int x: paths[path_id].nodes) {
                for (int child: tree[x]) {
                    // if depth is less, must've been parent, so skip
                    // this child node also cannot be within our current path, must be disjoint
                    if (depths[child] < depths[x] || paths[path_id].nodes.count(child)) {
                        continue;
                    }
                    accum += dp[child];
                }
            }
            opt_2 = max(opt_2, accum);
        }

        dp[now] = max(opt_1, opt_2);
    };

    dfs(1, 0);
    printf("%d\n", dp[1]);
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}