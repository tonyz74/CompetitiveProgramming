#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, K;
int S, T;

#define INF (1e9)

vector<int> shortest;

vector<vector<pair<int, int> > > graph;

using p = pair<int, int>;

void dijkstra() {
    priority_queue<p, vector<p>, greater<p> > pq;
    for (int i = 0; i < N; i++) {
        pq.push(make_pair(shortest[i], i));
    }

    vector<bool> seen(N + 1, false);

    while (!pq.empty()) {
        p top = pq.top();
        pq.pop();

        int my_id = top.second;
        int my_wt = shortest[my_id];

        if (seen[my_id]) continue;
        seen[my_id] = true;

        for (p conn: graph[my_id]) {
            int w = conn.first + my_wt;
            if (w < shortest[conn.second]) {
                pq.push(make_pair(w, conn.second));
                shortest[conn.second] = w;
            }
        }
    }
}

int main(void) {
    cin >> N >> M >> K >> S >> T;
    graph.resize(N);
    for (int i = 0; i < M; i++) {
        int start, end, weight;
        cin >> start >> end >> weight;
        graph[start].push_back(make_pair(weight, end));
        graph[end].push_back(make_pair(weight, start));
    }

    shortest.resize(N, INF);
    shortest[S] = 0;
    dijkstra();

    for (int k = 1; k <= K; k++) {
        vector<int> dup = shortest;
        
        for (int i = 0; i < N; i++) {
            for (p conn: graph[i]) {
                dup[conn.second] = min(dup[conn.second], shortest[i]);
            }
        }

        shortest = dup;

        dijkstra();
    }

    printf("%d\n", shortest[T]);
}