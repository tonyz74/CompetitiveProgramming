#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>

using namespace std;

int N;

int marker = 1;
int cells[256][256];
int comps[256][256];

set<int> graph[256 * 256 + 4];
int node_size[256 * 256 + 4];
int node_team[256 * 256 + 4];

bool oob(pair<int, int> pt) {
    int i = pt.first;
    int j = pt.second;
    if (i < 0 || j < 0 || i >= N || j >= N) return true;
    else return false;
}

void fill_same(int i, int j) {
    int color = cells[i][j];
    deque<pair<int, int> > dq;
    dq.push_back(make_pair(i, j));

    node_team[marker] = color;

    while (!dq.empty()) {
        pair<int, int> top = dq.front();
        dq.pop_front();
        if (comps[top.first][top.second]) continue;

        comps[top.first][top.second] = marker;
        node_size[marker]++;

        vector<pair<int, int> > neighbors = {
            { top.first, top.second + 1 },
            { top.first, top.second - 1 },
            { top.first + 1, top.second },
            { top.first - 1, top.second },
        };

        for (auto p: neighbors) {
            if (oob(p)) continue;
            if (cells[p.first][p.second] == color && comps[p.first][p.second] == 0) {
                dq.push_back(make_pair(p.first, p.second));
            }
        }
    }
}

struct save {
    int start;
    int color1;
    int color2; 

    save(int s, int c1, int c2) {
        if (c2 < c1) std::swap(c1, c2);
        start = s;
        color1 = c1;
        color2 = c2;
    }

    bool operator<(const save& rhs) const {
        return make_tuple(start, color1, color2) < make_tuple(rhs.start, rhs.color1, rhs.color2);
    }
};

set<save> cache;

int bfs(int start, int color1, int color2) {
    deque<int> dq;
    dq.push_back(start);

    int ans = 0;

    while (!dq.empty()) {
        int top = dq.front();
        dq.pop_front();
        if (cache.count(save(top, color1, color2))) continue;

        ans += node_size[top];
        cache.insert(save(top, color1, color2));

        for (int conn: graph[top]) {
            bool is_same_color = node_team[conn] == color1 || node_team[conn] == color2;
            if (!cache.count(save(conn, color1, color2)) && is_same_color) {
                dq.push_back(conn);
            }
        }
    }

    return ans;
}

int main(void) {
    freopen("multimoo.in", "r", stdin);
    freopen("multimoo.out", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> cells[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (comps[i][j] == 0) {
                fill_same(i, j);
                marker++;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            vector<pair<int, int> > nbs = {
                { i + 1, j },
                { i - 1, j },
                { i, j + 1 },
                { i, j - 1 }
            };

            for (auto nb: nbs) {
                if (oob(nb)) continue;
                if (comps[nb.first][nb.second] == comps[i][j]) continue;
                graph[comps[nb.first][nb.second]].insert(comps[i][j]);
                graph[comps[i][j]].insert(comps[nb.first][nb.second]);
            }
        }
    }

    int best_ans = 0;
    int best_single = 0;

    for (int i = 1; i < marker; i++) {
        best_single = max(best_single, node_size[i]);

        for (int conn: graph[i]) {
            int c1 = node_team[i];
            int c2 = node_team[conn];

            if (!cache.count(save(i, c1, c2))) {
                int ans = bfs(i, c1, c2);
                best_ans = max(best_ans, ans);
            }
        }
    }

    printf("%d\n%d\n", best_single, best_ans);
}