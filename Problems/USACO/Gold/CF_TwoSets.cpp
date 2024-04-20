#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>

using namespace std;

int N, A, B;

#define A_GROUP 1
#define B_GROUP 2
#define MAX_N ((int) (1e5 + 4))

struct edge {
    int dst;
    int grp;

    edge() {}
    edge(int d, int g): dst(d), grp(g) {}

    bool operator<(const edge& rhs) const {
        return make_pair(dst, grp) < make_pair(rhs.dst, rhs.grp);
    }
};

set<edge> graph[MAX_N];

vector<int> p;

unordered_map<int, int> lut;
vector<int> group_of_i;

bool is_cycle;
vector<bool> cyclefinder_vis;
vector<int> endpoints;

void dfs(int now, int parent) {
    cyclefinder_vis[now] = true;

    int went = 0;
    for (edge conn: graph[now]) {
        if (conn.dst == parent) continue;
        went++;

        // well, not a leaf
        if (cyclefinder_vis[conn.dst]) {
            is_cycle = true;
            continue;
        }

        dfs(conn.dst, now);
    }

    if (went == 0 || (parent == -1 && went == 1)) {
        endpoints.push_back(now);
    }
}

// get successor that's not been seen in a vis array
edge get_succ(int now, const vector<bool>& vis) {
    for (edge i: graph[now]) {
        // allow picking self
        if (i.dst == now || !vis[i.dst]) {
            return i;
        }
    }

    return edge(-1, -1);
}

bool choose_chain(int start) {
    // pick an adjacent, don't care who (we start from an endpoint in a
    // non cycle anyways), then keep picking every other one
    vector<bool> vis(N + 1, 0);

    int now = start;
    while (true) {
        vis[now] = true;
        // pick two at a time
        edge conn = get_succ(now, vis);
        if (conn.dst == -1) return false;

        vis[conn.dst] = true;
        group_of_i[now] = conn.grp;
        group_of_i[conn.dst] = conn.grp;

        int next_start = conn.dst;
        edge after = get_succ(next_start, vis);
        // at the very end, it succeeded (or i ignored a self loop)
        if (after.dst == -1 || after.dst == next_start) {
            return true;
        }

        now = after.dst;
    }
}

int main(void) {
    cin >> N >> A >> B;
    cyclefinder_vis.resize(N + 1);
    p.resize(N + 1);
    group_of_i.resize(N + 1);

    unordered_set<int> elems;

    for (int i = 1; i <= N; i++) {
        cin >> p[i];
        elems.insert(p[i]);
        lut[p[i]] = i;
    }

    for (int i = 1; i <= N; i++) {
        int e = p[i];

        if (elems.count(A - e)) {
            graph[lut[A - e]].insert(edge(i, A_GROUP));
            graph[i].insert(edge(lut[A - e], A_GROUP));
        }

        if (elems.count(B - e)) {
            graph[lut[B - e]].insert(edge(i, B_GROUP));
            graph[i].insert(edge(lut[B - e], B_GROUP));
        }
    }

    for (int i = 1; i <= N; i++) {
        if (!cyclefinder_vis[i]) {
            // printf("[i: %d]\n", i);
            is_cycle = false;
            endpoints.clear();
            dfs(i, -1);

            // must be a chain
            if (!is_cycle) {
                // single node with nowhere to go
                if (endpoints.size() != 2) {
                    printf("NO\n");
                    return 0;
                }

                int e1 = endpoints[0];
                if (!choose_chain(e1)) {
                    printf("NO\n");
                    return 0;
                }

            } else {

                if (endpoints.size() != 0) {
                    // means we have a self loop in here somewhere, at one of the endpoints
                    assert(choose_chain(endpoints[0]) == true);
                } else {
                    // just a normal cycle
                    assert(choose_chain(i) == true);
                }

            }
        }
    }

    printf("YES\n");
    for (int i = 1; i <= N; i++) {
        printf("%d ", group_of_i[i] - 1);
    }
    printf("\n");
}