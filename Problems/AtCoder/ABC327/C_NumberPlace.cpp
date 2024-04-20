#include <iostream>

using namespace std;

int grid[10][10];

int count_vals(bool values[10]) {
    int len = 0;
    for (int v = 1; v <= 9; v++) {
        len += values[v];
    }
    return len;
}

bool row_ok(int row) {
    bool values[10] = {0};
    
    for (int col = 1; col <= 9; col++) {
        values[grid[row][col]] = 1;
    }

    return count_vals(values) == 9;
}

bool col_ok(int col) {
    bool values[10] = {0};
    
    for (int row = 1; row <= 9; row++) {
        values[grid[row][col]] = 1;
    }

    return count_vals(values) == 9;
}

bool subreg_ok(int row, int col) {
    bool values[10] = {0};

    int d[3] = { -1, 0, 1 };
    for (int r_d = 0; r_d < 3; r_d++) {
        for (int c_d = 0; c_d < 3; c_d++) {
            values[grid[row + d[r_d]][col + d[c_d]]] = true;
        }
    }

    return count_vals(values) == 9;
}

int main(void) {
    for (int row = 1; row <= 9; row++) {
        for (int column = 1; column <= 9; column++) {
            cin >> grid[row][column];
        }
    }

    for (int x = 1; x <= 9; x++) {
        if (!row_ok(x) || !col_ok(x)) {
            // printf("No (%d) %d, %d\n", x, row_ok(x), col_ok(x));
            printf("No\n");
            return 0;
        }
    }

    int coords[9][2] = {
        { 2, 2 }, { 5, 2 }, { 8, 2 },
        { 2, 5 }, { 5, 5 }, { 8, 5 },
        { 2, 8 }, { 5, 8 }, { 8, 8 }
    };

    for (int x = 0; x < 9; x++) {
        if (!subreg_ok(coords[x][0], coords[x][1])) {
            // printf("failed a subregion check at %d %d\n", coords[x][0], coords[x][1]);
            printf("No\n");
            return 0;
        }
    }
    
    printf("Yes\n");
}