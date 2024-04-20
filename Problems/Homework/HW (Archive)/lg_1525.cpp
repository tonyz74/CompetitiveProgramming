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
        for (int i = 0; i < N; i++) {
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

struct conflict {
    int p1, p2;
    int rage;
};

bool cmp(const conflict& lhs, const conflict& rhs) {
    return lhs.rage > rhs.rage;
}

int main(void) {
    int N;
    cin >> N;

    int M;
    cin >> M;

    // each prisoner has an ID
    disjoint_set dsu(N);

    vector<conflict> cf(M);
    for (int i = 0; i < M; i++) {
        cin >> cf[i].p1 >> cf[i].p2 >> cf[i].rage;
    }

    sort(cf.begin(), cf.end(), cmp);

    for (int i = 0; i < M; i++) {
        // printf("trying to add relation between %d and %d\n", cf[i].p1, cf[i].p2);
        bool success = dsu.unite(cf[i].p1, cf[i].p2);

        if (!success) {
            // printf("failed at %d -> %d\n", cf[i].p1, cf[i].p2);
            printf("%d\n", cf[i].rage);
            return 0;
        }
    }

    printf("0\n");
}