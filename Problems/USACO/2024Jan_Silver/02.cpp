#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
using i64 = long long;

#define MAX_N (i64(1e5 + 4))

i64 N;
vector<i64> tree[MAX_N];
i64 pots[MAX_N];

bool seen[MAX_N];
i64 depth[MAX_N];
set<i64> leaves;

bool vis[MAX_N];
bool potion_will_appear[MAX_N];

void dfs(i64 node, i64 d) {
    if (seen[node]) return;
    seen[node] = true;
    depth[node] = d;

    for (i64 conn: tree[node]) {
        if (seen[conn] == false) {
            dfs(conn, d + 1);
        }
    }

    if (tree[node].size() == 1)  {
        leaves.insert(node);
    }
}

bool has_pot[MAX_N];

void go_up(int now) {
    vis[now] = true;

    for (i64 conn: tree[now]) {
        if (vis[conn] == false && depth[conn] < depth[now]) {
            // printf("heading to %lld from %d\n", conn, now);
            go_up(conn);
        }
    }
}

void go_down(int now) {
    vis[now] = true;

    // printf("going down from %d\n", now);

    i64 with_no_pots = -1;
    i64 with_pot = -1;
    for (i64 conn: tree[now]) {
        if (vis[conn] == false && depth[conn] > depth[now]) {
            if (!has_pot[conn]) {
                with_no_pots = conn;
                break;
            } else {
                with_pot = conn;
            }
        }
    }

    if (with_no_pots != -1) {
        go_down(with_no_pots);
        // printf("picked no pot path %lld\n", with_no_pots);
    } else if (with_pot != -1) {
        go_down(with_pot);
        // printf("picked pot path %lld\n", with_pot);
    }

    if (tree[now].size() == 1) {
        leaves.erase(now);
    }
}

void dfs_down_for_pot(int pos) {
    has_pot[pos] = true;

    for (int conn: tree[pos]) {
        if (has_pot[pos] == false && depth[conn] > depth[pos]) {
            dfs_down_for_pot(conn);
        }
    }
}

int main(void) {
    cin >> N;
    for (i64 i = 1; i <= N; i++) {
        cin >> pots[i];
    }

    for (i64 i = 1; i <= N - 1; i++) {
        i64 start, end; cin >> start >> end;
        tree[start].push_back(end);
        tree[end].push_back(start);
    }

    dfs(1, 0);

    i64 n_travs = leaves.size();
    vector<i64> usable_pots;
    for (i64 i = 1; i <= n_travs; i++) {
        usable_pots.push_back(pots[i]);
    }

    vector<i64> pots_by_depth = usable_pots;
    std::sort(
        pots_by_depth.begin(), pots_by_depth.end(),
        [] (i64 lhs, i64 rhs) {
            return depth[lhs] > depth[rhs];
        }
    );

    for (i64 p: pots_by_depth) {
        dfs_down_for_pot(p);
    }

    // for (i64 n = 1; n <= N; n++) {
    //     printf("%d ", has_pot[n]);
    // }

    i64 ans = 0;
    for (i64 p: usable_pots) {
        bool no_paths_down = true;
        for (i64 conn: tree[p]) {
            if (vis[conn] == false && depth[conn] > depth[p]) {
                // printf("%lld can still go to %lld\n", p, conn);
                no_paths_down = false;
            }
        }

        if (!no_paths_down || leaves.count(p)) {
            // printf("doing %lld\n", p);
            ans++;
            go_up(p);
            go_down(p);
        }
    }

    printf("%lld\n", ans);
    // printf("%lld\n", n_travs);
}