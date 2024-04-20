#include <iostream>
#include <queue>

using namespace std;

struct conn {
    int end;
    int wt;

    conn() {}
    conn(int e, int w) : end(e), wt(w) {}

    // i used a greater than to sort the other way
    bool operator<(const conn& rhs) const {
        return this->wt > rhs.wt;
    }
};

int N, M, Q;
vector<vector<conn> > graph;

// even: [1, N]
// odd: [N + 1, 2N]

int main(void) {
    cin >> N >> M >> Q;
    graph.resize(2 * N + 4);

    for (int i = 1; i <= M; i++) {
        // we don't have to judge based on THEIR parity,
        // we have our own system, us not adding is just like
        // doing a transformation to our space that's just + 0,
        // because we want to save space.
        int st, ed; cin >> st >> ed;

        // my even node has to connect to their odd node
        // and vice versa (double that for directionality)

        graph[st].push_back(conn(ed + N, 1));   // my even node to their odd node
        graph[ed + N].push_back(conn(st, 1));   // their odd node to my even node

        graph[st + N].push_back(conn(ed, 1));   // my odd node to their even node
        graph[ed].push_back(conn(st + N, 1));   // their even node to my odd node
    }

    vector<int> shortest(2 * N + 4, 1e9);
    vector<bool> seen(2 * N + 4, false);

    priority_queue<conn> pq;
    pq.push(conn(1, 0));

    // 1 costing 0 will always be even path
    shortest[1] = 0;

    while (!pq.empty()) {
        conn top = pq.top();
        pq.pop();

        if (seen[top.end]) continue;
        seen[top.end] = true;

        for (conn c: graph[top.end]) {
            int v = shortest[top.end] + c.wt;
            if (v < shortest[c.end]) {
                pq.push(conn(c.end, v));
                shortest[c.end] = v;
                // printf("updating shortest[%d] to %d from shortest[%d]\n", c.end, v, top.end);
            }
        }
    }

    for (int q = 0; q < Q; q++) {
        int x, L;
        cin >> x >> L;

        // try to find my distance to their odd or even node
        // depending on their parity (shortest even path or shortest odd path)
        int target = x;
        if (L % 2 == 1) {
            target += N;
        }

        if (shortest[target] <= L) printf("Yes\n");
        else printf("No\n");
    }
}