#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int N;
int marker = 1;
#define MAX_GROUPS ((int) (1e6 + 4))

char grid[1024][1024];
int group[1024][1024];

int area[MAX_GROUPS];
int perimeter[MAX_GROUPS];

int nb_off[4][2] = {
    { 1, 0 },
    { -1, 0 },
    { 0, 1 },
    { 0, -1 }
};

int is_oob(int i, int j) {
    return i <= 0 || i > N || j <= 0 || j > N;
}

void dfs(int i, int j) {
    if (group[i][j] != 0) return;
    group[i][j] = marker;
    area[marker]++;

    for (int nb = 0; nb < 4; nb++) {
        int new_i = i + nb_off[nb][0];
        int new_j = j + nb_off[nb][1];
        if (is_oob(new_i, new_j) || grid[new_i][new_j] == '.') {
            perimeter[marker]++;
            continue;
        }

        if (group[new_i][new_j] == 0 && grid[new_i][new_j] == '#') {
            dfs(new_i, new_j);
        }
    }
}

int main(void) {
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        string S; cin >> S;
        for (int j = 0; j < N; j++) {
            grid[i][j + 1] = S[j];
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (group[i][j] == 0 && grid[i][j] == '#') {
                dfs(i, j);
                marker++;
            }
            // printf("%d ", group[i][j]);
        }
        // printf("\n");
    }

    map<int, vector<int> > perims_with_area;

    for (int i = 1; i < marker; i++) {
        perims_with_area[area[i]].push_back(perimeter[i]);
    }

    int mx_area = perims_with_area.rbegin()->first;
    int mn_perim = 2e9;
    for (int perim: perims_with_area.rbegin()->second) {
        mn_perim = min(mn_perim, perim);
    }
    printf("%d %d\n", mx_area, mn_perim);
}