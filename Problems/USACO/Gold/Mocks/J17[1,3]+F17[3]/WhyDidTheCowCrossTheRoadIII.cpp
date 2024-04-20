#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct coord {
    int i, j;
    coord() {}
    coord(int row, int col): i(row), j(col) {}
    bool operator<(const coord& rhs) const {
        return make_pair(i, j) < make_pair(rhs.i, rhs.j);
    }
};

int N, K, R;
set<pair<coord, coord> > roads;

int marker = 1;
int group[101][101];

void dfs(int i, int j) {
    group[i][j] = marker;

    int conn[4][2] = {
        { i + 1, j },
        { i - 1, j },
        { i, j + 1 },
        { i, j - 1 },
    };

    for (int c = 0; c < 4; c++) {
        int new_i = conn[c][0];
        int new_j = conn[c][1];

        // out of bounds
        if (new_i <= 0 || new_i > N || new_j <= 0 || new_j > N) continue;
        // cannot take a road
        if (roads.count(make_pair(coord(i, j), coord(new_i, new_j)))) continue;
        // already been visited
        if (group[new_i][new_j] != 0) continue;

        dfs(new_i, new_j);
    }

}

int main(void) {
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);

    cin >> N >> K >> R;
    for (int i = 1; i <= R; i++) {
        int r, c, r1, c1; cin >> r >> c >> r1 >> c1;
        roads.insert(make_pair(coord(r, c), coord(r1, c1)));
        roads.insert(make_pair(coord(r1, c1), coord(r, c)));
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (group[i][j] == 0) {
                dfs(i, j);
                marker++;
            }

            // printf("%d ", group[i][j]);
        }
        // printf("\n");
    }

    vector<coord> cows(K + 1);
    for (int i = 1; i <= K; i++) cin >> cows[i].i >> cows[i].j;

    int ans = 0;
    for (int i = 1; i <= K; i++) {
        for (int j = i + 1; j <= K; j++) {
            coord c1 = cows[i];
            coord c2 = cows[j];

            if (group[c1.i][c1.j] != group[c2.i][c2.j]) {
                ans++;
            }
        }
    }

    printf("%d\n", ans);
}