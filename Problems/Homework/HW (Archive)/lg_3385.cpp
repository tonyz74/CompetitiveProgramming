#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct conn {
    int ep;
    int wt;

    conn(int e, int w) {
        this->ep = e;
        this->wt = w;
    }
};

void solve(void) {
    int n, m;
    cin >> n >> m;

    vector<vector<conn> > graph(n + 1);

    for (int i = 0; i < m; i++) {
        int st, ed, wt;
        cin >> st >> ed >> wt;

        if (wt >= 0) {
            graph[st].push_back(conn(ed, wt));
            graph[ed].push_back(conn(st, wt));
        } else {
            graph[st].push_back(conn(ed, wt));
        }
    }

    queue<int> next_process;
    next_process.push(1);
    vector<int> shortest_paths(n + 1, 1e9);
    vector<int> which_move(n + 1, 1e9);
    shortest_paths[1] = 0;
    which_move[1] = 0;
    vector<bool> in_queue(n + 1, false);
    in_queue[1] = true;

    while (!next_process.empty()) {
        int me_rn = next_process.front();
        next_process.pop();
        in_queue[me_rn] = false;

        int my_len = shortest_paths[me_rn];
        for (auto c: graph[me_rn]) {
            int possible_wt = my_len + c.wt;
            if (possible_wt < shortest_paths[c.ep]) {
                shortest_paths[c.ep] = possible_wt;
                which_move[c.ep] = which_move[me_rn] + 1;

                // in case of a negative cycle, you'd always get stuck and
                // reach this point eventually. putting it here is fine.
                if (which_move[c.ep] >= n) {
                    printf("YES\n");
                    return;
                }

                if (!in_queue[c.ep]) {
                    next_process.push(c.ep);
                    in_queue[c.ep] = true;
                }
            }
        }
    }

    printf("NO\n");
}

int main(void) {
    // Idea: run SPFA until done, or until the number of vertices
    // traveled to reach the current vertex exceeds the number
    // of vertices in the graph (a cycle was taken, and only negative
    // cycles would be profitable).

    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        solve();
    }
}