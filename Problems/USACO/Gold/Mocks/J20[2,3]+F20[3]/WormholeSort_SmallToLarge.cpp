#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

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

vector<int> parent;
vector<set<int> > elems;
set<int> not_connnected_yet;
vector<int> current_pos;

// nodes 1~n inclusive
void init_dsu() {
    parent.resize(N + 1);
    elems.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        elems[i].insert(i);

        if (current_pos[i] != i) {
            not_connnected_yet.insert(i);
        }
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x);
    int py = find(y);

    if (px == py) return;

    // assume px always has less elems than py, swap if not true
    if (elems[px].size() > elems[py].size()) {
        std::swap(px, py);
    }

    // printf("\nmerging %d and %d\n", x, y);
    parent[px] = py;
    for (int elem: elems[px]) {
        elems[py].insert(elem);
        parent[elem] = py;

        // printf("adding %d to set %d\n", elem, py);
        if (find(current_pos[elem]) == find(elem) && not_connnected_yet.count(elem)) {
            // printf("erasing %d\n", elem);
            not_connnected_yet.erase(elem);
        }

        // person who needs to connect to elem?
        if (find(p[elem]) == find(current_pos[p[elem]]) && not_connnected_yet.count(p[elem])) {
            // printf("erasing %d\n", p[elem]);
            not_connnected_yet.erase(p[elem]);
        }
    }
    elems[px].clear();
}

int main(void) {
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);

    cin >> N >> M;
    p.resize(N + 1);
    current_pos.resize(N + 1);
    wormholes.resize(M + 1);

    for (int i = 1; i <= N; i++) {
        cin >> p[i];
        current_pos[p[i]] = i;
    }


    for (int i = 1; i <= M; i++) {
        cin >> wormholes[i].src >> wormholes[i].dst >> wormholes[i].width;
    }
    std::sort(wormholes.begin() + 1, wormholes.end());

    init_dsu();

    if (not_connnected_yet.empty()) {
        printf("-1\n");
        return 0;
    }

    for (int i = 1; i <= M; i++) {
        unite(wormholes[i].src, wormholes[i].dst);

        if (not_connnected_yet.empty()) {
            printf("%d\n", wormholes[i].width);
            return 0;
        }
    }
}