#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int N;
map<int, vector<int> > adj;

int max_diameter = 0;

int search_tree(int current_dist, int parent, int now) {
    vector<int> distances;

    for (int child: adj[now]) {
        if (child != parent) {
            distances.push_back(search_tree(current_dist + 1, now, child));
        }
    }

    std::sort(distances.begin(), distances.end());
    std::reverse(distances.begin(), distances.end());

    // one of the subtrees might contain the max diameter
    if (distances.size() >= 2) {
        max_diameter = max(max_diameter, distances[0] + distances[1] - 2 * current_dist);
    }
    max_diameter = max(max_diameter, current_dist);

    if (distances.empty()) return current_dist;
    return distances[0];
}

int main(void) {
    cin >> N;

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // assume 1 is the root
    search_tree(0, -1, 1);
    cout << max_diameter << endl;
}