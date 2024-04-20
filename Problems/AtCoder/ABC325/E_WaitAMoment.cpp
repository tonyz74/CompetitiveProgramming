#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;
using p = pair<ll, int>;

#define INF 1e18

ll N, A, B, C;
ll D[1024][1024];

vector<ll> dijkstra(int N, vector<vector<p> > graph, int start_node) {
    vector<ll> best_paths(N + 1, INF);
    vector<bool> seen(N + 1, false);
    priority_queue<p, vector<p>, greater<p> > pq;

    pq.push(make_pair(0, start_node));
    best_paths[start_node] = 0;

    while (!pq.empty()) {
        p top = pq.top();
        pq.pop();

        if (seen[top.second]) continue;
        seen[top.second] = true;

        for (auto conn: graph[top.second]) {
            ll nwt = conn.first + top.first;
            if (nwt < best_paths[conn.second]) {
                best_paths[conn.second] = nwt;
                pq.push(make_pair(nwt, conn.second));
            }
        }
    }

    return best_paths;
}

int main(void) {
    cin >> N >> A >> B >> C;

    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
        cin >> D[i][j];
    }

    vector<vector<p> > adj_list_car(N + 1);
    vector<vector<p> > adj_list_train(N + 1);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) continue;

            adj_list_car[i].push_back(make_pair(D[i][j] * A, j));
            adj_list_train[i].push_back(make_pair(D[i][j] * B + C, j));
        }
    }

    // shortest path from city 1 to city i
    vector<ll> ssp_car = dijkstra(N, adj_list_car, 1);
    // shortest path from city i to end
    vector<ll> ssp_train = dijkstra(N, adj_list_train, N);

    ll best = ssp_car[N];
    best = min(best, ssp_train[1]);

    // only check ones in between now
    for (int i = 1; i < N; i++) {
        best = min(best, ssp_car[i] + ssp_train[i]);
    }

    cout << best << endl;
}