#include <iostream>
#include <vector>
#include <string_view>
#include <set>
#include <deque>
#include <array>
#include <cstring>

using namespace std;

#define EMPTY 0
#define WALL 1
#define COMMAND 2
#define BESSIE 3
#define BOARD_STATES (19683 + 12)

struct tile {
    int type;
    int row, col;
    int v;

    static tile wall() {
        tile t; t.type = WALL;
        return t;
    }

    static tile empty() {
        tile t; t.type = EMPTY;
        return t;
    }

    static tile cmd(int i, int j, int val) {
        tile t;
        t.type = COMMAND;
        t.row = i;
        t.col = j;
        t.v = val;
        return t;
    }

    static tile bessie() {
        tile t; t.type = BESSIE;
        return t;
    }
};

struct ttt {
    int data[3][3];

    ttt() {
        memset(data, 0, sizeof(data));
    }

    int is_win() {
        for (int i = 0; i < 3; i++) {
            if ((data[i][0] == 1 && data[i][1] == 2 && data[i][2] == 2)
                || (data[i][0] == 2 && data[i][1] == 2 && data[i][2] == 1)) {
                return true;
            }

            if ((data[0][i] == 1 && data[1][i] == 2 && data[2][i] == 2)
                || (data[0][i] == 2 && data[1][i] == 2 && data[2][i] == 1)) {
                return true;
            }
        }

        if ((data[0][0] == 1 && data[1][1] == 2 && data[2][2] == 2)
            || (data[0][0] == 2 && data[1][1] == 2 && data[2][2] == 1)) {
            return true;
        }

        if ((data[2][0] == 1 && data[1][1] == 2 && data[0][2] == 2)
            || (data[2][0] == 2 && data[1][1] == 2 && data[0][2] == 1)) {
            return true;
        }

        return false;
    }

};

int N;
ttt board;
tile grid[30][30];
bool has_seen[25][25][BOARD_STATES];
set<int> unique_wins;
int pow3[14];

bool check_num_win(int bstate) {
    ttt board;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board.data[i][j] = bstate % 3;
            bstate /= 3;
        }
    }

    return board.is_win();
}

void search(int i, int j, int compressed) {
    if (has_seen[i][j][compressed]) return;
    has_seen[i][j][compressed] = true;

    // if (just_transitioned) {
    // printf("i=%d, j=%d\n", i, j);
    // board.print();
    // print_grid();
    // }

    if (grid[i][j].type == COMMAND) {
        auto cmd = grid[i][j];
        int pow = cmd.row * 3 + cmd.col;

        int mod = pow3[pow + 1];
        if ((compressed % mod) / pow3[pow] == 0) {
            compressed += cmd.v * pow3[pow];
        }

        if (check_num_win(compressed)) {
            unique_wins.insert(compressed);
            return;
        }
    }

    vector<pair<int, int> > neighbors = {
        { i + 1, j },
        { i - 1, j },
        { i, j + 1 },
        { i, j - 1 }
    };

    for (auto nb: neighbors) {
        if (nb.first < 0 || nb.first >= N || nb.second < 0 || nb.second >= N)
            continue;
        if (grid[nb.first][nb.second].type == WALL)
            continue;
        
        search(nb.first, nb.second, compressed);
    }
}

int main(void) {
    int k = 1;
    for (int i = 0; i < 14; i++) {
        pow3[i] = k;
        k *= 3;
    }

    cin >> N;
    int si = 0;
    int sj = 0;

    for (int i = 0; i < N; i++) {
        string S_orig; cin >> S_orig;
        string_view sv = S_orig;

        int c = 0;
        for (int j = 0; j < 3 * N; j += 3) {
            string_view slice = sv.substr(j, 3);
            if (slice == "###") {
                grid[i][c] = tile::wall();
            } else if (slice == "BBB") {
                grid[i][c] = tile::bessie();
                si = i;
                sj = c;
            } else if (slice == "...") {
                grid[i][c] = tile::empty();
            } else {
                int row = slice[1] - '0' - 1;
                int col = slice[2] - '0' - 1;
                if (slice[0] == 'M') grid[i][c] = tile::cmd(row, col, 1);
                else grid[i][c] = tile::cmd(row, col, 2);
            }

            c++;
        }
    }

    search(si, sj, 0);
    printf("%d\n", (int) unique_wins.size());
}