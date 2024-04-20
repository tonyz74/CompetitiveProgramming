#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;
#define MAX_N ((int) 1e5 + 4)

i64 N;
vector<i64> tree[MAX_N];
i64 pots[MAX_N];
i64 n_leaves[MAX_N];

i64 dp[MAX_N];
i64 pots_at[MAX_N];

// note: when writing dp on number of leaves below for trees,
// we usually consider leaves to have one leaf below (themselves).
i64 find_n_leaves(i64 now, i64 prev) {
    i64 ans = 0;
    for (i64 x: tree[now]) {
        if (x != prev) {
            ans += find_n_leaves(x, now);
        }
    }

    n_leaves[now] = max(1ll, ans);
    return n_leaves[now];
}

void dfs(i64 now, i64 prev) {
    i64 below = 0;

    for (i64 conn: tree[now]) {
        if (conn != prev) {
            dfs(conn, now);
            below += dp[conn];
        }
    }

    // max capacity of all children vs what i can take on using
    // spare branches of the children
    dp[now] = min(n_leaves[now], below + pots_at[now]);
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

    i64 leaves = find_n_leaves(1, 0);
    // printf("n leaves: %lld\n", leaves);

    for (i64 i = 1; i <= leaves; i++) {
        pots_at[pots[i]]++;
    }
     
    dfs(1, 0);
    printf("%lld\n", dp[1]);
}