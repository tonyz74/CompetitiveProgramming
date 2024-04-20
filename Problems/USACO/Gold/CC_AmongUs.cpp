#include <iostream>
#include <vector>

using namespace std;

int marker = 1;
int fail = false;
vector<int> groups;
vector<int> coloring;
vector<vector<int> > d_nbrs;
vector<vector<int> > s_nbrs;

void dfs(int curr, int color) {
    groups[curr] = marker;
    coloring[curr] = color;

    for (int x: d_nbrs[curr]) {
        if (coloring[x] != 0 && coloring[x] == coloring[curr]) {
            fail = true;
        }
        if (coloring[x] == 0) {
            dfs(x, (color == 1) ? 2 : 1);
        }
    }

    for (int x: s_nbrs[curr]) {
        if (coloring[x] != 0 && coloring[x] != coloring[curr]) {
            fail = true;
        }
        if (coloring[x] == 0) {
            dfs(x, color);
        }
    }
}

void solve() {
    s_nbrs.clear();
    d_nbrs.clear();
    groups.clear();
    coloring.clear();
    marker = 1;
    fail = false;

    int N, Q; cin >> N >> Q;
    d_nbrs.resize(N + 2);
    s_nbrs.resize(N + 2);
    groups.resize(N + 2);
    coloring.resize(N + 2);
    fail = false;

    for (int i = 0; i < Q; i++) {
        int ty, from, to;
        cin >> ty >> from >> to;

        if (ty == 1) {
            d_nbrs[from].push_back(to);
            d_nbrs[to].push_back(from);
        } else {
            s_nbrs[from].push_back(to);
            s_nbrs[to].push_back(from);
        }
    }
 
    vector<vector<int> > comps(N + 2);

    for (int i = 1; i <= N; i++) {
        if (groups[i] == 0) {
            dfs(i, 1);
            marker++;
        }

        comps[groups[i]].push_back(i);
    }

    if (fail) {
        printf("-1\n");
        return;
    }

    int ans = 0;
    for (int i = 1; i < marker; i++) {
        int n_ones = 0;
        int n_twos = 0;

        for (int x: comps[i]) {
            if (coloring[x] == 1) n_ones++;
            else if (coloring[x] == 2) n_twos++;
            else if (coloring[x] == 0) {
                printf("error!\n");
            }
        }

        ans += max(n_ones, n_twos);
    }

    printf("%d\n", ans);
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
}