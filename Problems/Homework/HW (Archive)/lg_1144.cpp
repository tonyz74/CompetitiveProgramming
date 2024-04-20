#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

using p = pair<int, int>;

int main(void) {
    int N, M;
    cin >> N >> M;

    vector<vector<int> > graph(N + 1);
    for (int i = 0; i < M; i++) {
        int st, ed;
        cin >> st >> ed;
        graph[st].push_back(ed);
        graph[ed].push_back(st);
    }

    vector<int> n_paths(N + 1, 0);
    vector<int> shortest_paths(N + 1, 1e9);

    n_paths[1] = 1;
    shortest_paths[1] = 0;
    priority_queue<p, vector<p>, greater<p> > pq;
    vector<bool> has_seen(N + 1, false);
    pq.push(make_pair(0, 1));

    while (!pq.empty()) {
        p rn = pq.top();
        pq.pop();

        if (has_seen[rn.second]) {
            continue;
        }
        has_seen[rn.second] = true;

        for (int ep : graph[rn.second]) {
            int maybe_new_best = shortest_paths[rn.second] + 1;
            if (maybe_new_best < shortest_paths[ep]) {
                pq.push(make_pair(maybe_new_best, ep));
                shortest_paths[ep] = maybe_new_best;
                n_paths[ep] = 0;
            }

            if (maybe_new_best == shortest_paths[ep]) {
                n_paths[ep] += n_paths[rn.second];
                n_paths[ep] = n_paths[ep] % 100003;
            }
        }
    }

    for (int i = 1; i < N + 1; i++) {
        cout << n_paths[i] << endl;
    }
}