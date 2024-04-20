#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, Q;
vector<vector<int> > graph;

struct best_paths {
    int best_even;
    int best_odd;

    best_paths() {}
    best_paths(int e, int o) : best_even(e), best_odd(o) {}
};

struct update_info {
    int dist;
    int parity;
    int end;

    bool operator<(const update_info& rhs) {
        return this->dist > rhs.dist;
    }
};

vector<best_paths> shortest;

int main(void) {
    cin >> N >> M >> Q;

    graph.resize(M + 1);
    shortest.resize(N + 1, best_paths(1e9, 1e9 + 1));

    for (int i = 1; i <= M; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    priority_queue<update_info> pq;
    shortest[1].best_even = 0;
    shortest[1].best_odd = 1e9;

    update_info init;
    init.dist = 0;
    init.end = 1;
    init.parity = 0;
    pq.push(init);

    while (!pq.empty()) {
        update_info top = pq.top();
        pq.pop();

        
    }
}