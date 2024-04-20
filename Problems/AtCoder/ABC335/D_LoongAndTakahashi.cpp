#include <iostream>
#include <vector>

using namespace std;

int grid[1024][1024];

enum dir {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

int moves[4][2] = {
    { -1, 0 },
    { 1, 0 },
    { 0, -1 },
    { 0, 1 }
};

dir change_dir(dir current) {
    if (current == UP) {
        return RIGHT;
    } else if (current == DOWN) {
        return LEFT;
    } else if (current == RIGHT) {
        return DOWN;
    } else if (current == LEFT) {
        return UP;
    }

    return UP;
}

int main(void) {
    int N; cin >> N;

    dir curr_dir = RIGHT;
    int counter = 1;
    int row = 0, col = 0;

    while (counter != N * N) {
        int new_row = row + moves[curr_dir][0]; 
        int new_col = col + moves[curr_dir][1]; 

        if (new_row < 0 || new_row >= N || new_col < 0 || new_col >= N
            || grid[new_row][new_col] != 0) {
            curr_dir = change_dir(curr_dir);
        } else {
            grid[row][col] = counter++;
            row = new_row;
            col = new_col;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j && i == N / 2) {
                printf("T");
            } else {
                printf("%d", grid[i][j]);
            }

            if (j != N - 1) printf(" ");
        }
        printf("\n");
    }
}