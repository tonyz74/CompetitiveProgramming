#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int grid[100][10];
bool filled[100][10];

int N, K;

vector<pair<int, int> > to_remove;

void dfs(int i, int j) {
    pair<int, int> coords[] = {
        { i - 1, j },
        { i + 1, j },
        { i, j - 1 },
        { i, j + 1 }
    };

    to_remove.push_back(make_pair(i, j));
    filled[i][j] = true;

    for (auto p: coords) {
        if (p.first < 0 || p.first >= N) {
            continue;
        } else if (p.second < 0 || p.second >= 10) {
            continue;
        }

        if (filled[p.first][p.second] == 0
            && grid[p.first][p.second] == grid[i][j]) {
            dfs(p.first, p.second);
        }
    }
}

int main(void) {
    freopen("mooyomooyo.in", "r", stdin);
    freopen("mooyomooyo.out", "w", stdout);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        for (int j = 0; j < 10; j++) {
            grid[i][j] = S[j] - '0';
        }
    }

    while (true) {
        memset(filled, 0, sizeof(filled));
        bool worked = false;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 10; j++) {
                if (!filled[i][j] && grid[i][j] != 0) {
                    dfs(i, j);

                    if ((int) to_remove.size() >= K) {
                        // printf("%d: ", grid[i][j]);
                        for (auto p: to_remove) {
                            grid[p.first][p.second] = 0;
                            // printf("(%d, %d) ", p.first, p.second);
                        }
                        worked = true;
                    }

                    to_remove.clear();
                }
            }
        }

        if (!worked) break;

        for (int col = 0; col < 10; col++) {
            vector<int> to_add;
            for (int row = N - 1; row >= 0; row--) {
                if (grid[row][col] != 0) {
                    to_add.push_back(grid[row][col]);
                }
                grid[row][col] = 0;
            }

            int i = 0;
            for (int row = N - 1; row >= 0; row--) {
                if (i >= (int) to_add.size()) break;
                grid[row][col] = to_add[i++];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}
