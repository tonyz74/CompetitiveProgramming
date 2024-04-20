#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cstring>

using namespace std;

char grid[24][24];
struct rect {
    int r1, c1;
    int r2, c2;
};

vector<rect> rects;

rect bounds;
int group_id = 1;
int groups[21][21];

void fill(int r, int c, char color) {
    if (groups[r][c] != 0) return;

    groups[r][c] = group_id;

    vector<pair<int, int> > neighbors = {
        { r + 1, c },
        { r - 1, c },
        { r, c + 1 },
        { r, c - 1 }
    };

    for (auto nbr: neighbors) {
        if (nbr.first < bounds.r1 || nbr.first > bounds.r2
            || nbr.second < bounds.c1 || nbr.second > bounds.c2) {
            continue;
        }

        if (groups[nbr.first][nbr.second] == 0
            && grid[nbr.first][nbr.second] == color) {
            fill(nbr.first, nbr.second, color);
        }
    }
}

bool covers_rect(rect a, rect b) {
    if (a.r1 <= b.r1 && a.r2 >= b.r2 && a.c1 <= b.c1 && a.c2 >= b.c2) {
        return true;
    }
    return false;
}

bool is_pcl(int r1, int c1, int r2, int c2) {
    group_id = 1;
    memset(groups, 0, sizeof(groups));
    map<char, set<int>> groups_by_color;
    bounds = (rect) { r1, c1, r2, c2 };

    for (int r = r1; r <= r2; r++) {
        for (int c = c1; c <= c2; c++) {
            if (groups[r][c] == 0) {
                fill(r, c, grid[r][c]);
                groups_by_color[grid[r][c]].insert(groups[r][c]);
                group_id++;
            }
        }
    }

    if (groups_by_color.size() == 2) {
        int num_ones = 0;
        for (const auto &s: groups_by_color) {
            // printf("%c => %d\n", s.first, (int) s.second.size());
            if (s.second.size() == 1) num_ones++;
        }

        return num_ones == 1;
    }

    return false;
}

int main(void) {
    freopen("where.in", "r", stdin);
    freopen("where.out", "w", stdout);

    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
        string S; cin >> S;
        for (int j = 1; j <= N; j++) {
            grid[i][j] = S[j - 1];
        }
    } 

    for (int r1 = 1; r1 <= N; r1++) {
        for (int c1 = 1; c1 <= N; c1++) {
            for (int r2 = r1; r2 <= N; r2++) {
                for (int c2 = c1; c2 <= N; c2++) {
                    if (is_pcl(r1, c1, r2, c2)) {
                        rects.push_back((rect) { r1, c1, r2, c2 });
                    }
                }
            }
        }
    }

    int real_pcls = 0;
    for (int i = 0; i < (int) rects.size(); i++) {
        int none_overlap = true;
        for (int j = 0; j < (int) rects.size(); j++) {
            if (i == j) continue;

            // if j covers i, don't add i
            if (covers_rect(rects[j], rects[i])) {
                none_overlap = false;
                break;
            }
        }

        real_pcls += (int) none_overlap;
    }

    printf("%d\n", real_pcls);
}