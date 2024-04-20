#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> p;

int main(void) {
    vector<vector<p> > graph;

    // N -> number of vertices
    // M -> number of edges
    int N, M;

    cin >> N >> M;
    graph.resize(N + 1);

    for (int i = 0; i < M; i++) {
        int start, end, weight;
        cin >> start >> end >> weight;

        // weight comes first
        graph[start].push_back(make_pair(weight, end));
    }

    vector<p> best_paths(N + 1, pair<int, int>(1e9, 1e9));
    vector<pair<bool, bool> > is_known(N + 1, pair<int, int>(false, false));

    // second value denotes first or second best path candidate
    priority_queue<p, vector<p>, greater<p> > to_update;
    to_update.push(make_pair(1, 1));
    best_paths[1].first = 0;

    while (!to_update.empty()) {
        p top = to_update.top();
        int this_node = top.second;
        to_update.pop();

        // skip if both are known
        if (is_known[this_node].first && is_known[this_node].second) {
            continue;
        }

        // we will always ascertain the best path before the second best
        if (is_known[this_node].first) {
            is_known[this_node].second = true;
        } else {
            is_known[this_node].first = true;
        }

        for (auto conn: graph[this_node]) {
            int weight = conn.first;
            int endpoint = conn.second;

            int candidates[] = {
                best_paths[this_node].first + weight,
                best_paths[this_node].second + weight
            };

            for (int i = 0; i < 2; i++) {
                int maybe = candidates[i];
                int current_first = best_paths[endpoint].first;
                
                if (maybe < current_first) {
                    best_paths[endpoint].second = current_first;
                    best_paths[endpoint].first = maybe;

                    // both have been updated, might be ascertained
                    to_update.push(make_pair(current_first, endpoint));
                    to_update.push(make_pair(maybe, endpoint));

                } else if (maybe < best_paths[endpoint].second && maybe != current_first) {

                    best_paths[endpoint].second = maybe;
                    to_update.push(make_pair(maybe, endpoint));

                }
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("to node %d: %d, %d\n", i, best_paths[i].first, best_paths[i].second);
    }
}