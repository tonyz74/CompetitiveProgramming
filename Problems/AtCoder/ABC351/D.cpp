#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;


int H, W;
int mapping[1005][1005];
char grid[1005][1005];
int vis[1005][1005];
int group_cnt = 0;

unordered_map<int, unordered_set<int> > reach;

bool oob(int i, int j) {
    if (i <= 0 || i > H) return true;
    if (j <= 0 || j > W) return true;
    return false;
}

bool has_adj_magnet(int i, int j) {
    int checks[4][2] = {
        {i - 1, j},
        {i + 1, j},
        {i, j - 1},
        {i, j + 1}
    };

    for (int chk = 0; chk < 4; chk++) {
        if (oob(checks[chk][0], checks[chk][1])) continue;
        if (grid[checks[chk][0]][checks[chk][1]] == '#') {
            return true;
        }
    }

    return false;
}

void dfs(int i, int j) {
    if (oob(i, j)) return;
    if (vis[i][j] != 0) return;

    reach[group_cnt].insert(mapping[i][j]);
    if (has_adj_magnet(i, j)) {
        return;
    }
    vis[i][j] = group_cnt;

    dfs(i + 1, j);
    dfs(i - 1, j);
    dfs(i, j + 1);
    dfs(i, j - 1);
}

int main(void) {
    cin >> H >> W;

    int id = 1;
    for (int i = 1; i <= H; i++) {
        string s; cin >> s;
        for (int j = 0; j < W; j++) {
            grid[i][j + 1] = s[j];
            mapping[i][j + 1] = id++;
        }
    }

    int mx = 0;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (grid[i][j] == '#') continue;

            if (!vis[i][j]) {
                ++group_cnt;
                dfs(i, j);
                mx = max(mx, (int) reach[group_cnt].size());
            }
        }
    }

    // cout << vis[2][3] << endl;
    // for (auto j: reach[3]) {
    //     printf("[%d] ", j);
    // }
    // cout << endl;
    cout << mx << endl;
}
