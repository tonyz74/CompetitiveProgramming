#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main(void) {
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);
    int N, M; cin >> N >> M;

    vector<vector<int> > graph(N + 1);
    for (int i = 0; i < M; i++) {
        int f1, f2;
        cin >> f1 >> f2;
        graph[f1].push_back(f2);
        graph[f2].push_back(f1);
    }

    vector<int> coloring(N + 1);
    for (int v = 1; v <= N; v++) {
        int color = 1;

        set<int> invalid_colors;
        for (int neighbor: graph[v]) {
            if (coloring[neighbor] != 0) {
                invalid_colors.insert(coloring[neighbor]);
            }
        }

        while (invalid_colors.count(color)) color++;
        coloring[v] = color;
    }

    for (int i = 1; i <= N; i++) {
        cout << coloring[i];
    }
    cout << endl;
}