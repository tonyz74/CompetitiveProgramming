#include <iostream>
#include <vector>
#include <set>

using namespace std;

int N;
vector<vector<int> > graph;
vector<int> coloring;

void color_tree(int node, int parent) {
    int color = 1;

    for (int conn: graph[node]) {
        // printf("x: %d\n", conn);
        if (conn == parent) continue;

        while (color == coloring[node] || color == coloring[parent]) color++;
        coloring[conn] = color;
        // printf("%d coloring %d\n", node, conn);
        color_tree(conn, node);
        color++;
    }
}

int main(void) {
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);

    cin >> N;
    graph.resize(N + 1);
    coloring.resize(N + 1, 0);

    for (int i = 0; i < N - 1; i++) {
        int s, e;
        cin >> s >> e;
        graph[s].push_back(e);
        graph[e].push_back(s);
    }

    // starting from any point is ok, so just start
    // from farm 1
    coloring[1] = 1;
    color_tree(1, 1);

    set<int> unq;
    for (int i = 1; i <= N; i++) {
        unq.insert(coloring[i]);
        // printf("vertex %d: color %d\n", i, coloring[i]);
    }
    cout << unq.size() << endl;
}