#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_N ((int) (1e5 + 5))

using i64 = long long;

i64 grp_cnt = 1;
i64 grp_ids[MAX_N];
vector<i64> adj[MAX_N];

i64 find_closest_elem(const set<i64>& S, i64 elem) {
    // first one not less than
    auto lb = S.lower_bound(elem);
    if (lb == S.end()) return *S.rbegin();

    if (lb != S.begin()) {
        auto pre = lb;
        pre--;

        if (elem - *pre < *lb - elem) {
            return *pre;
        }
    }

    return *lb;
}

void dfs(i64 curr, i64 prev) {
    grp_ids[curr] = grp_cnt;
    for (i64 conn: adj[curr]) {
        if (conn != prev && grp_ids[conn] == 0)
            dfs(conn, curr);
    }
}

void solve() {
    i64 N, M; cin >> N >> M;

    grp_cnt = 1;
    memset(grp_ids, 0, sizeof(grp_ids));
    for (i64 i = 0; i < MAX_N; i++) adj[i].clear();

    for (i64 i = 0; i < M; i++) {
        i64 s, e; cin >> s >> e;
        adj[s].push_back(e);
        adj[e].push_back(s);
    } 

    for (i64 x = 1; x <= N; x++) {
        if (grp_ids[x] == 0) {
            dfs(x, -1);
            grp_cnt++;
        }
    }

    vector<set<i64> > groups(grp_cnt);
    for (i64 x = 1; x <= N; x++) {
        groups[grp_ids[x]].insert(x);
    }

    i64 start_group = grp_ids[1];
    i64 end_group = grp_ids[N];

    vector<pair<i64, i64> > best_dists(grp_cnt, make_pair(1e18, 1e18));
    for (i64 g = 1; g < grp_cnt; g++) {
        for (i64 member: groups[g]) {
            i64 best_end = find_closest_elem(groups[end_group], member);
            i64 best_start = find_closest_elem(groups[start_group], member);

            best_dists[g].first = min(
                best_dists[g].first,
                (best_start - member) * (best_start - member)
            );

            best_dists[g].second = min(
                best_dists[g].second,
                (best_end - member) * (best_end - member)
            );
        }
    }

    i64 ans = 1e18;
    for (i64 g = 1; g < grp_cnt; g++) {
        // printf("(g: %lld), %lld and %lld\n", g, best_dists[g].first, best_dists[g].second);
        ans = min(ans, best_dists[g].first + best_dists[g].second);
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t; cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
}
