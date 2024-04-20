#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct disjoint_set_union {
    vector<int> parent_of;
    
    // nodes 1 to =N
    disjoint_set_union(int N) {
        parent_of.resize(N + 1);
        for (int i = 1; i <= N; i++) {
            parent_of[i] = i;
        }
    }

    int find(int x) {
        if (parent_of[x] != x) {
            parent_of[x] = find(parent_of[x]);
        }

        return parent_of[x];
    }

    void combine(int x, int y) {
        // reparent the leader of x under y
        parent_of[find(x)] = find(y);
    }
};

int main(void) {
    freopen("hoofball.in", "r", stdin);
    freopen("hoofball.out", "w", stdout);

    int N; cin >> N;

    if (N == 1) {
        printf("1\n");
        return 0;
    };

    vector<pair<int, int> > x(N + 1);
    vector<int> pos_lookup(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> x[i].first;
        x[i].second = i;
        pos_lookup[i] = x[i].first;
    }
    sort(x.begin(), x.end());

    disjoint_set_union dsu(N);   

    vector<int> incoming(N + 1, 0);
    vector<int> connections(N + 1, -1);

    assert(N >= 2);
    for (int i = 1; i <= N; i++) {
        int best_dist = 1e9;
        int neighbor = -1;

        if (i - 1 >= 1) {
            best_dist = x[i].first - x[i - 1].first;
            neighbor = x[i - 1].second;
        }

        if (i + 1 <= N) {
            int right_dist = x[i + 1].first - x[i].first;
            if (right_dist < best_dist) {
                best_dist = right_dist;
                neighbor = x[i + 1].second;
            }
        }

        connections[x[i].second] = neighbor;
        incoming[neighbor]++;
        // printf("uniting %d@%d with %d@%d\n", x[i].second, pos_lookup[x[i].second], neighbor, pos_lookup[neighbor]);
        dsu.combine(neighbor, x[i].second);
    }

    vector<int> leaders;
    map<int, vector<int> > groups;

    for (int i = 1; i <= N; i++) {
        int parent = dsu.find(i);
        if (parent == i) {
            leaders.push_back(i);
        }
        groups[parent].push_back(i);
    }

    int total_balls = 0;

    for (int lead: leaders) {
        bool perfect_cycle = true;
        for (int cow: groups[lead]) {
            if (incoming[cow] == 0) {
                perfect_cycle = false;
                total_balls++;
            }
        }

        if (perfect_cycle) {
            total_balls++;
        }
    }

    cout << total_balls << endl;
}