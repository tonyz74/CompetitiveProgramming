#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct pt {
    int x, y;
};

struct moo_net {
    int min_x = 1e9;
    int max_x = -1e9;
    int min_y = 1e9;
    int max_y = -1e9;
};

vector<pt> cows;
vector<vector<int> > graph;

int marker = 1;
vector<int> group_of;
map<int, moo_net> networks;

void dfs(int node) {
    group_of[node] = marker;
    for (int conn: graph[node]) {
        if (group_of[conn] == 0) {
            dfs(conn);
        }
    }
}


void setIO() {
    #ifndef TZ74_LOCAL_TESTING
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);
    #endif
}

int main(void) {
    setIO();

    int N; cin >> N;
    int M; cin >> M;

    cows.resize(N + 1);
    graph.resize(N + 1);
    group_of.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> cows[i].x >> cows[i].y;
    }

    for (int i = 1; i <= M; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= N; i++) {
        if (group_of[i] == 0) {
            dfs(i);
            marker++;
        }

        int g = group_of[i];
        networks[g].max_x = max(networks[g].max_x, cows[i].x);
        networks[g].min_x = min(networks[g].min_x, cows[i].x);
        networks[g].max_y = max(networks[g].max_y, cows[i].y);
        networks[g].min_y = min(networks[g].min_y, cows[i].y);
    }    

    int min_perim = 2e9;
    for (auto p: networks) {
        moo_net net = p.second;
        min_perim = min(min_perim, 2 * (net.max_x - net.min_x) + 2 * (net.max_y - net.min_y));
    }

    cout << min_perim << endl;
}