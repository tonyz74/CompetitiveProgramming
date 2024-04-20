#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

int grid[1024][1024];
bool vis[1024][1024];

vector<pair<int, int> > translations {
    { -1, -1 },
    { -1, 0 },
    { -1, 1 },
    { 0, -1 },
    { 0, 1 },
    { 1, -1 },
    { 1, 0 },
    { 1, 1 }
};

#define within_bounds(r, c) ((r) > 0 && (r <= H) && (c > 0) && (c <= W))

int main(void) {
    int H, W;
    cin >> H >> W;

    for (int row = 1; row <= H; row++) {
        string S; cin >> S;

        for (int col = 1; col <= W; col++) {
            grid[row][col] = S[col - 1];
        }
    }

    int counter = 0;

    for (int r = 1; r <= H; r++) for (int c = 1; c <= W; c++) {
        if (grid[r][c] == '#') {
            // remove connected component
            queue<pair<int, int> > q;
            q.push(make_pair(r, c));

            while (!q.empty()) {
                int tr = q.front().first; int tc = q.front().second;
                grid[tr][tc] = '.';
                
                q.pop();
                if (vis[tr][tc]) continue;

                for (auto tl: translations) {
                    int nr = tr + tl.first; int nc = tc + tl.second;
                    if (within_bounds(nr, nc) && grid[nr][nc] == '#') q.push(make_pair(nr, nc));
                }
                vis[tr][tc] = true;
            }

            counter++;
        }
    }

    cout << counter << endl;
}