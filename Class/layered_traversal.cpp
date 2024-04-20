#include <iostream>
#include <vector>
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

int N, M, K;
int S, T;

vector<vector<conn> > graph;

int layered_node(int l, int i) {
    return (l * N + i);
}

int main(void) {
    cin >> N >> M >> K;
    cin >> S >> T;

    graph.resize(N * (K + 1) + 4);

    for (int i = 0; i < M; i++) {
        int start, end, wt; cin >> start >> end >> wt;

        for (int layer = 0; layer <= K; layer++) {
            graph[layered_node(layer, start)].push_back(
                conn(layered_node(layer, end), wt)
            );

            graph[layered_node(layer, end)].push_back(
                conn(layered_node(layer, start), wt)
            );

            // connect this layer to the next one unidirectionally
            // (these are the free paths they could take)

            if (layer < K) {
                graph[layered_node(layer, start)].push_back(
                    conn(layered_node(layer + 1, end), 0)
                );
                graph[layered_node(layer, end)].push_back(
                    conn(layered_node(layer + 1, start), 0)
                );
            }
        }
    }

    vector<int> shortest((K + 1) * N + 4, 1e9);
    vector<bool> seen((K + 1) * N + 4, false);

    priority_queue<conn> pq;
    pq.push(conn(S, 0));
    shortest[S] = 0;

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

    // no more layers to go down to
    if (K == 0) {
        printf("%d\n", shortest[T]);
    } else {
        // because we can take back and forth free flights repeatedly,
        // we only need to check the two maximum K's with different parities,
        // and one of them will have the min value.
        
        printf("%d\n", min(shortest[K * N + T], shortest[(K - 1) * N + T]));
    }
}