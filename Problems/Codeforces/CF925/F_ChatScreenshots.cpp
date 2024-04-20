#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

vector<set<int> > graph;

void solve() {
    int n, k; cin >> n >> k;
    graph.clear();
    graph.resize(n + 1, set<int>());

    vector<vector<int> > a(k + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 1; i <= k; i++) {
        for (int j = 2; j <= n - 1; j++) {
            int first = a[i][j];
            int second = a[i][j + 1];

            graph[first].insert(second);
            // printf("connect %d to %d\n", first, second);
        }
    }

    map<int, int> incoming;
    for (int i = 1; i <= n; i++) incoming[i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int conn: graph[i]) {
            incoming[conn]++;
        }
    }

    deque<int> zeroes;
    for (int i = 1; i <= n; i++) {
        if (incoming[i] == 0) {
            zeroes.push_back(i);
            incoming.erase(i);
        }
    }

    while (!zeroes.empty()) {
        int z = zeroes.front();
        zeroes.pop_front();

        // printf("take %d\n", z);

        for (int x: graph[z]) {
            incoming[x]--;
            if (incoming[x] == 0) {
                zeroes.push_back(x);
                incoming.erase(x);
            }
        }
    }

    if (!incoming.empty()) {
        printf("NO\n");
        return;
    }

    printf("YES\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}