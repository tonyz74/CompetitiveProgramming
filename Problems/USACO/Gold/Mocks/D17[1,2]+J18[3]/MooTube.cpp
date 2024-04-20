#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 5001

int N, Q;
vector<int> seen;
vector<vector<int> > R;
vector<int> tree[MAX_N];

#define REL_SELF ((int) 2e9)

void reset_seen() {
    for (int i = 1; i <= N; i++) seen[i] = 0;
}

void dfs(int src, int now) {
    seen[now] = true;

    for (int ch: tree[now]) {
        if (seen[ch]) continue;

        R[src][ch] = min(R[src][now], R[now][ch]);
        // undirected
        R[ch][src] = R[src][ch];

        dfs(src, ch);
    }
}

int main(void) {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    cin >> N >> Q;
    seen.resize(N + 1);
    R.resize(N + 1, vector<int>(N + 1, 0));

    for (int i = 1; i <= N - 1; i++) {
        int p, q, r; cin >> p >> q >> r;
        R[p][q] = r;
        R[q][p] = r;
        tree[p].push_back(q);
        tree[q].push_back(p);
    }
    for (int i = 1; i <= N; i++) {
        R[i][i] = REL_SELF;
    }

    for (int i = 1; i <= N; i++) {
        reset_seen();
        dfs(i, i);
    }

    // for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= N; j++) {
    //         if (i == j) printf("X ");
    //         else printf("%d ", R[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int q = 1; q <= Q; q++) {
        int k, v; cin >> k >> v;
        int ans = 0;
        for (int i = 1; i <= N; i++) {
            if (i == v) continue;
            if (R[v][i] >= k) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
}