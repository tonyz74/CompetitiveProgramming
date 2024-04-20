#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main(void) {
    int n, k; cin >> n >> k;
    vector<pair<int, int> > d(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> d[i].first;
        d[i].second = i;
    }

    int n_zeroes = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i].first == 0) n_zeroes++;
    }
    if (n_zeroes != 1) {
        printf("%d\n", -1);
        return 0;
    }

    std::sort(d.begin() + 1, d.end());

    set<int> gone;
    map<int, set<pair<int, int> > > nodes_with_dist;
    for (int i = 1; i <= n; i++) {
        // with distance [DIST] there's node with current degree count [0] and id of [ID]
        nodes_with_dist[d[i].first].insert(make_pair(0, d[i].second));
    }

    vector<vector<int> > graph(n + 1, vector<int>());

    // connect to the parent with the smallest current degree, just check the 
    // k property at the very end
    for (int i = 2; i <= n; i++) {
        int from = d[i].first - 1;
        set<pair<int, int> >& nodes = nodes_with_dist[from];
        
        if (nodes.empty()) {
            printf("%d\n", -1);
            return 0;
        }

        // front has min degree
        auto min_deg_node = *nodes.begin();
        nodes.erase(nodes.begin());
        min_deg_node.first++;

        graph[min_deg_node.second].push_back(d[i].second);
        graph[d[i].second].push_back(min_deg_node.second);

        nodes.insert(min_deg_node);
    }

    set<pair<int, int> > edges;

    for (int i = 1; i <= n; i++) {
        for (int x: graph[i]) {
            edges.insert(make_pair(min(i, x), max(i, x)));
        }
    }
    
    map<int, int> degree;
    for (auto edge: edges) {
        degree[edge.first]++;
        degree[edge.second]++;
    }

    for (int i = 1; i <= n; i++) {
        if (degree[i] > k) {
            printf("-1\n");
            return 0;
        }
    }

    printf("%d\n", (int) edges.size());
    for (auto edge: edges) {
        printf("%d %d\n", edge.first, edge.second);
    }

}