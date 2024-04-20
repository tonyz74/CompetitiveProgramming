#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct wormhole {
    int width;
    int src, dst;

    wormhole() {}
    wormhole(int w, int s, int d): width(w), src(s), dst(d) {}

    // we want big widths to go first
    bool operator<(const wormhole& rhs) const {
        return width > rhs.width;
    }
};

int N, M;
vector<int> p;
vector<wormhole> wormholes;

struct dsu {
    vector<int> parent;

    // nodes 1~n inclusive
    dsu(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }
};

int main(void) {
    // freopen("wormsort.in", "r", stdin);
    // freopen("wormsort.out", "w", stdout);

    cin >> N >> M;
    p.resize(N + 1);
    wormholes.resize(M + 1);

    for (int i = 1; i <= N; i++) {
        cin >> p[i];
    }

    for (int i = 1; i <= M; i++) {
        cin >> wormholes[i].src >> wormholes[i].dst >> wormholes[i].width;
    }
    std::sort(wormholes.begin() + 1, wormholes.end());

    int matches = true;
    for (int i = 1; i <= N; i++) {
        if (i != p[i]) {
            matches = false;
        }
    }
    // already sorted
    if (matches) {
        printf("-1\n");
        return 0;
    }

    dsu union_find(N);

    for (int i = 1; i <= M; i++) {
        union_find.unite(wormholes[i].src, wormholes[i].dst);

        int all = true;
        for (int i = 1; i <= N; i++) {
            // if p[i] can't get to i, not ok
            if (union_find.find(p[i]) != union_find.find(i)) {
                all = false;
            }
        }

        if (all) {
            printf("%d\n", wormholes[i].width);
            return 0;
        }
    }

    printf("-1\n");
}