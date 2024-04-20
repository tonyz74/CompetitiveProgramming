#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;
using i64 = long long;

#define MAX_N ((i64) (1e5 + 3))

i64 N;
i64 dst[MAX_N];

i64 marker = 1;
i64 group_ids[MAX_N];
vector<i64> comps[MAX_N];

vector<i64> graph_bidir[MAX_N];

void dfs(i64 x) {
    group_ids[x] = marker;
    for (i64 conn: graph_bidir[x]) {
        if (group_ids[conn] == 0) {
            dfs(conn);
        }
    }
}

int main(void) {
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    cin >> N;
    for (i64 i = 1; i <= N; i++) {
        cin >> dst[i];

        graph_bidir[i].push_back(dst[i]);
        if (dst[i] != i) {
            graph_bidir[dst[i]].push_back(i);
        }
    }

    for (i64 i = 1; i <= N; i++) {
        if (group_ids[i] == 0) {
            dfs(i);
            marker++;
        }
        comps[group_ids[i]].push_back(i);
    }

    i64 ans = 0;

    for (i64 mark = 1; mark < marker; mark++) {
        deque<i64> zero_in;
        map<i64, i64> in_cnt;
        vector<i64> topo;

        for (i64 x: comps[mark]) {
            in_cnt[dst[x]]++;
        }
        for (i64 x: comps[mark]) {
            if (in_cnt[x] == 0) {
                zero_in.push_back(x);
            }
        }

        while (!zero_in.empty()) {
            i64 top = zero_in.front();

            in_cnt.erase(top);
            topo.push_back(top);
            zero_in.pop_front();

            in_cnt[dst[top]]--;
            if (in_cnt[dst[top]] == 0) {
                zero_in.push_back(dst[top]);
            }
        }

        ans += in_cnt.size();
    }

    cout << ans << endl;
}