#include <iostream>
#include <vector>
#include <functional>

using namespace std;

void setIO() {
#ifndef TZ74_LOCAL_TESTING
    freopen("moop.in", "r", stdin);
    freopen("moop.out", "w", stdout);
#endif
}

int main(void) {
    setIO();

    int N; cin >> N;
    vector<int> x(N + 1);
    vector<int> y(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> x[i] >> y[i];
    }

    vector<vector<int> > graph(N + 1, vector<int>());

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) { 
            if (x[i] <= x[j] && y[i] <= y[j]) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    int marker = 1;
    vector<int> group_of(N + 1);
    function<void(int)> dfs = [&] (int i) {
        if (group_of[i] != 0) return;
        group_of[i] = marker;

        for (int adj: graph[i]) {
            if (group_of[adj] == 0) {
                dfs(adj);
            }
        }
    };

    for (int i = 1; i <= N; i++) {
        if (group_of[i] == 0) {
            dfs(i);
            marker++;
        }
    }

    cout << (marker - 1) << endl;
}