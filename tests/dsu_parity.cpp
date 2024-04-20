#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct set_elem {
    int id;
    int parity;

    set_elem() {
        id = 0;
        parity = 0;
    }
};

struct disjoint_set {
    vector<set_elem> parents;

    disjoint_set(int N) {
        parents.resize(N + 1);
        for (int i = 0; i <= N; i++) {
            parents[i].id = i;
            parents[i].parity = 0;
        }
    }

    bool unite(int x, int y) {
        set_elem par_x = find(x);
        set_elem par_y = find(y);

        if (par_x.id == par_y.id && par_x.parity == par_y.parity) {
            // didn't succeed
            return false;
        }

        parents[par_x.id].id = par_y.id;
        parents[par_x.id].parity = par_x.parity ^ par_y.parity ^ 1;
        return true;
    }

    set_elem find(int id) {
        if (id != parents[id].id) {
            char my_parity = parents[id].parity;
            set_elem parent = find(parents[id].id);
            parent.parity ^= my_parity;
            parents[id] = parent;
        }

        return parents[id];
    }
};

void print_parents(disjoint_set& dsu) {
    for (int i = 0; i < dsu.parents.size(); i++) {
        if (dsu.parents[i].id == i) continue;
        printf("[%d] -> parent %d, parity to root %d\n", i, dsu.parents[i].id, dsu.parents[i].parity);
    }
}

int main(void) {
    disjoint_set dsu(14);
    dsu.unite(9, 10);
    dsu.unite(10, 11);
    dsu.unite(11, 12);

    print_parents(dsu);

    printf("\n");
    printf("%d %d\n", dsu.find(10).id, dsu.find(10).parity);
    printf("%d %d\n", dsu.find(12).id, dsu.find(12).parity);

    printf("\n");
    print_parents(dsu);

    printf("\n");

    dsu.unite(10, 4);
    print_parents(dsu);
}