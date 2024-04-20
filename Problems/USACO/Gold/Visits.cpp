#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;
using i64 = long long;

struct edge {
    i64 dst;
    i64 wt;
};

const int MAX_N = (2 * 1e5) + 10;

i64 marker = 1;
i64 groups[MAX_N];

edge conn[MAX_N];
vector<i64> graph_bidir[MAX_N];

vector<i64> components[MAX_N];

void dfs(i64 curr) {
    groups[curr] = marker;
    for (i64 x: graph_bidir[curr]) {
        if (groups[x] == 0) {
            dfs(x);
        }
    } 
}

int main(void) { 
    i64 N; cin >> N;

    for (i64 i = 1; i <= N; i++) {
        cin >> conn[i].dst >> conn[i].wt;

        graph_bidir[i].push_back(conn[i].dst);
        if (conn[i].dst != i) {
            graph_bidir[conn[i].dst].push_back(i);
        }
    }

    for (i64 i = 1; i <= N; i++) {
        if (groups[i] == 0) {
            dfs(i);
            marker++;
        }
        components[groups[i]].push_back(i);
    }

    i64 total = 0;

    for (i64 mark = 1; mark < marker; mark++) {
        map<i64, i64> in_edges;
        deque<i64> zero_in;

        for (i64 x: components[mark]) {
            in_edges[conn[x].dst]++;
        }
        for (i64 x: components[mark]) {
            if (in_edges[x] == 0) {
                zero_in.push_back(x);
            }
        }

        vector<i64> topo;
        while (!zero_in.empty()) {
            i64 top = zero_in.front();

            zero_in.pop_front();
            in_edges.erase(top);
            topo.push_back(top);
            total += conn[top].wt;

            in_edges[conn[top].dst]--;
            if (in_edges[conn[top].dst] == 0) {
                zero_in.push_front(conn[top].dst);
            }
        }

        i64 min_wt = 1e18;
        for (i64 x: components[mark]) {
            if (in_edges.count(x)) {
                min_wt = min(min_wt, conn[x].wt);
                total += conn[x].wt;
            }
        }
        if (min_wt != 1e18) {
            total -= min_wt;
        }
    }

    cout << total << endl;
}