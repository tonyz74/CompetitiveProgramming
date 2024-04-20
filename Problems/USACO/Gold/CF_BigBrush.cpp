#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct op {
    int i, j;
    int color;
    op(int row, int col, int c): i(row), j(col), color(c) {}
};

int n, m;
vector<op> moves;
deque<op> todo;

#define MAX_DIM 1001
#define UNKNOWN ((int) 1e9)

int grid[MAX_DIM][MAX_DIM];

int get_color(int i, int j) {
    int other = -1;
    int colors[4] = {
        grid[i][j],
        grid[i][j + 1],
        grid[i + 1][j],
        grid[i + 1][j + 1]
    };

    // cannot be all unknowns, cannot have duplicate, non unknown colors
    for (int i = 0; i < 4; i++) {
        if (colors[i] != UNKNOWN) {
            if (other == -1 || other == colors[i]) {
                other = colors[i];
            } else {
                return false;
            }
        }
    }

    if (other == -1) return 0;
    else return other;
}

int main(void) {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= m - 1; j++) {
            int c = get_color(i, j);
            if (c != 0) {
                todo.push_back(op(i, j, c));
            }
        }
    }

    while (!todo.empty()) {
        op top = todo.front();
        todo.pop_front();

        if (get_color(top.i, top.j) == 0) continue;
        moves.push_back(top);

        for (int r_off = 0; r_off <= 1; r_off++) {
            for (int c_off = 0; c_off <= 1; c_off++) {
                grid[top.i + r_off][top.j + c_off] = UNKNOWN;
            }
        }

        for (int i_off = -1; i_off <= 1; i_off++) {
            int new_i = top.i + i_off;
            if (new_i <= 0 || new_i >= n) continue;

            for (int j_off = -1; j_off <= 1; j_off++) {
                int new_j = top.j + j_off;
                if (new_j <= 0 || new_j >= n) continue;

                int c = get_color(new_i, new_j);
                if (c != 0) {
                    todo.push_back(op(new_i, new_j, c));
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] != UNKNOWN) {
                printf("-1\n");
                return 0;
            }
        }
    }

    printf("%lu\n", moves.size());
    for (int i = (int) moves.size() - 1; i >= 0; i--) {
        printf("%d %d %d\n", moves[i].i, moves[i].j, moves[i].color);
    }
}