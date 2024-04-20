#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define MAX_N ((int) (2 * 1e5 + 4))

int N;
int marker = 1;
vector<int> bidir_conn[MAX_N];

int ans[MAX_N];
int succ[MAX_N];
int group[MAX_N];


void dfs(int curr) {
    group[curr] = marker;

    for (int next: bidir_conn[curr]) {
        if (group[next] == 0) {
            dfs(next);
        }
    }
}

int main(void) {

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> succ[i];

        bidir_conn[i].push_back(succ[i]);
        if (succ[i] != i) {
            bidir_conn[succ[i]].push_back(i);
        }
    }
    
    vector<vector<int> > comps(N + 1);

    for (int i = 1; i <= N; i++) {
        if (group[i] == 0) {
            dfs(i);
            marker++;
        }

        comps[group[i]].push_back(i);
    }

    for (int mark = 1; mark < marker; mark++) {
        map<int, int> in_edges;
        deque<int> zeroes;

        for (int x: comps[mark]) in_edges[succ[x]]++;
        for (int x: comps[mark]) {
            if (in_edges[x] == 0) {
                zeroes.push_back(x);
            }
        }

        vector<int> topo;

        while (!zeroes.empty()) {
            int top = zeroes.front();

            zeroes.pop_front();
            in_edges.erase(top);
            topo.push_back(top);

            in_edges[succ[top]]--;
            if (in_edges[succ[top]] == 0) {
                zeroes.push_back(succ[top]);
            }
        }

        int remaining = in_edges.size();
        for (auto p: in_edges) {
            ans[p.first] = remaining;
        }

        std::reverse(topo.begin(), topo.end());
        for (int i: topo) {
            ans[i] = ans[succ[i]] + 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", ans[i]);
    }
}