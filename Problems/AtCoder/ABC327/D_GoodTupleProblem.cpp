#include <iostream>
#include <vector>

using namespace std;

struct dsu_node {
    int parent;
    int parity;
};

struct dsu {
    vector<dsu_node> nodes;

    dsu(int N) {
        nodes.resize(N + 1);
        for (int i = 1; i <= N; i++) {
            nodes[i].parent = i;
            nodes[i].parity = 0;
        }
    }

    dsu_node find(int id) {
        if (nodes[id].parent != id) {
            int my_parity = nodes[id].parity;
            dsu_node res = find(nodes[id].parent);
            nodes[id].parent = res.parent;
            nodes[id].parity = res.parity ^ my_parity;
        }

        return nodes[id];
    }

    bool merge_bipartite(int g1, int g2) {
        dsu_node n1 = find(g1);
        dsu_node n2 = find(g2);

        if (n1.parent == n2.parent && n1.parity == n2.parity) {
            return false;
        }

        nodes[n1.parent].parent = n2.parent;
        nodes[n1.parent].parity = n2.parity ^ n1.parity ^ 1;

        return true;
    }
};

int main(void) {
    int N, M;
    cin >> N >> M;

    vector<int> A(M + 1); vector<int> B(M + 1);
    for (int i = 1; i <= M; i++) cin >> A[i];
    for (int i = 1; i <= M; i++) cin >> B[i];

    // keep adding relationships until bipartite fails
    dsu rels(N);

    bool failed = false;
    for (int i = 1; i <= M; i++) {
        if (!rels.merge_bipartite(A[i], B[i])) {
            failed = true;
            break;
        }
    }

    if (failed) {
        printf("No\n");
    } else {
        printf("Yes\n");
    }
}