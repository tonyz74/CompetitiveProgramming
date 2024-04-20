#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>

using namespace std;

typedef long long ll;

int N, M;
ll K;

struct dsu {
    vector<int> parent;

    dsu(int N) {
        parent.resize(N + 1);
        for (int i = 1; i <= N; i++) parent[i] = i;
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }

    int find(int node) {
        // compression
        if (parent[node] != node) {
            int p = find(parent[node]);
            parent[node] = p;
        }

        return parent[node];
    }
};

struct edge {
    int u, v;
    ll w;
};

vector<edge> edges;

int main(void) {
    cin >> N >> M >> K;
    edges.resize(M + 1);
    for (int i = 1; i <= M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].w %= K;
    }

    // printf("%d %d\n", edges[22].u, edges[22].v);

    vector<bool> in_use(M, false);
    // a MST has N - 1 edges
    for (int i = 0; i < N - 1; i++) in_use[i] = true;
    reverse(in_use.begin(), in_use.end());

    ll min_cost = 1e18;

    do {
        // printf("\npermutation:\n");
        ll new_val = 0;

        // see if can make a spanning tree
        dsu uf(N);

        for (int i = 0; i < M; i++) if (in_use[i]) {
            // edges are 1 indexed
            int edge_id = i + 1;
            // printf("%d %d %d\n", edge_id, edges[edge_id].u, edges[edge_id].v);
            new_val += edges[edge_id].w;
            new_val %= K;

            // if will make a cycle
            if (uf.find(edges[edge_id].u) == uf.find(edges[edge_id].v)) {
                goto next_perm;
            }
            
            // otherwise just keep making the mst
            uf.unite(edges[edge_id].u, edges[edge_id].v);
        }

        // printf("i found one\n");
        min_cost = min(min_cost, new_val % K);

        next_perm: (void) 1;

        // if (counter++ == 10) return 0;

    } while (next_permutation(in_use.begin(), in_use.end()));

    printf("%lld\n", min_cost);
}