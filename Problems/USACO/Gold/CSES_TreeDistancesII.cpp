#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

#define MAX_N ((i64) (2 * 1e5 + 3))

vector<i64> tree[MAX_N];
i64 n_nodes[MAX_N];
i64 ans[MAX_N];

i64 find_n_nodes(i64 node, i64 prev, i64 dist_to_root) {
    i64 x = 1;
    ans[1] += dist_to_root;

    for (i64 ch: tree[node]) {
        if (ch != prev) {
            x += find_n_nodes(ch, node, dist_to_root + 1);
        }
    }

    n_nodes[node] = x;
    return x;
}

void solve(i64 now, i64 prev) {
    if (now != 1) {
        ans[now] = ans[prev] - n_nodes[now] + (n_nodes[1] - n_nodes[now]);
    }

    for (i64 ch: tree[now]) {
        if (ch != prev) {
            solve(ch, now);
        }
    }
}

int main(void) {
    i64 n; cin >> n;
    for (i64 i = 0; i < n - 1; i++) {
        i64 s, e; cin >> s >> e;
        tree[s].push_back(e);
        tree[e].push_back(s);
    }

    find_n_nodes(1, 0, 0);

    solve(1, 0);
    for (i64 i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
}