#include <array>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

struct polyomino {
    // data[row][column]
    char data[4][4];

    polyomino() {
        memset(data, '.', sizeof(data));
    }
};

// spins by 90 degrees clockwise
polyomino rotate(const polyomino& src) {
    polyomino ret;
    
    // outer layer
    ret.data[0][3] = src.data[0][0];
    ret.data[1][3] = src.data[0][1];
    ret.data[2][3] = src.data[0][2];
    
    ret.data[3][3] = src.data[0][3];
    ret.data[3][2] = src.data[1][3];
    ret.data[3][1] = src.data[2][3];

    ret.data[3][0] = src.data[3][3];
    ret.data[2][0] = src.data[3][2];
    ret.data[1][0] = src.data[3][1];
    
    ret.data[0][0] = src.data[3][0];
    ret.data[0][1] = src.data[2][0];
    ret.data[0][2] = src.data[1][0];

    ret.data[1][1] = src.data[2][1];
    ret.data[1][2] = src.data[1][1];
    ret.data[2][2] = src.data[1][2];
    ret.data[2][1] = src.data[2][2];

    return ret;
}

polyomino read_input(void) {
    polyomino ret;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> ret.data[i][j];
        }
    }

    return ret;
}

void print_polynomio(const polyomino& src) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << src.data[i][j];
        }
        cout << endl;
    }
}

bool check_validity(vector<pair<pair<int, int>, const polyomino&> > &pairings) {
    char grid[4][4];
    memset(grid, '.', 4 * 4);
    
    for (auto& [pos, poly] : pairings) {
        int x = pos.first; int y = pos.second;

        for (int r = 0; r < 4; r++) for (int c = 0; c < 4; c++) {
            if (y + r >= 4 || x + c >= 4) {
                if (poly.data[r][c] == '#') {
                    // something sticking out
                    return false;
                } else {
                    // skip current iteration, prevent OOB
                    continue;
                }
            }

            if (grid[y + r][x + c] == '.') {
                grid[y + r][x + c] = poly.data[r][c];
            } else {
                // conflict
                if (poly.data[r][c] == '#') {
                    return false;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == '.') return false;
        }
    }

    return true;
}

pair<polyomino, bool> move_up(polyomino p) {
    for (int i = 0; i < 4; i++) {
        if (p.data[0][i] == '#') {
            return make_pair(polyomino(), false);
        }
    }

    polyomino ret;
    memcpy(&ret.data[0][0], &p.data[1], 4);
    memcpy(&ret.data[1][0], &p.data[2], 4);
    memcpy(&ret.data[2][0], &p.data[3], 4);

    return make_pair(ret, true);
}

pair<polyomino, bool> move_left(const polyomino x) {
    for (int i = 0; i < 4; i++) {
        if (x.data[i][0] == '#') {
            return make_pair(polyomino(), false);
        }
    }

    polyomino ret;
    for (int row = 0; row < 4; row++) {
        memcpy(&ret.data[row], &x.data[row][1], 3 * sizeof(char));
    }

    return make_pair(ret, true);
}

polyomino align_to_tl(const polyomino in) {
    polyomino p = in;

    while (true) {
        auto out = move_up(p);
        if (out.second == false) {
            break;
        }

        p = out.first;
    }

    while (true) {
        auto out = move_left(p);
        if (out.second == false) {
            break;
        }

        p = out.first;
    }

    return p;
}

int main(void) {
    auto in_1 = align_to_tl(read_input());
    auto in_2 = align_to_tl(read_input());
    auto in_3 = align_to_tl(read_input());

    // we can fix rotation of P1, because it's a square

    // 4 rotations of P2
    auto P1 = in_1;
    auto P2 = in_2;

    for (int rot_p2 = 0; rot_p2 < 4; rot_p2++) {
        if (rot_p2) { P2 = rotate(P2); P2 = align_to_tl(P2); }

        auto P3 = in_3;

        for (int rot_p3 = 0; rot_p3 < 4; rot_p3++) {
            if (rot_p3) { P3 = rotate(P3); P3 = align_to_tl(P3); }

            for (int x1 = 0; x1 < 4; x1++) for (int y1 = 0; y1 < 4; y1++) {
                for (int x2 = 0; x2 < 4; x2++) for (int y2 = 0; y2 < 4; y2++) {
                    for (int x3 = 0; x3 < 4; x3++) for (int y3 = 0; y3 < 4; y3++) {

                        vector<pair<pair<int, int>, const polyomino&> > pairings = {
                            {make_pair(x1, y1), P1},
                            {make_pair(x2, y2), P2},
                            {make_pair(x3, y3), P3}
                        };

                        if (check_validity(pairings) == true) {
                            cout << "Yes" << endl;
                            return 0;
                        }

                    }
                }
            }
        }
    }

    cout << "No" << endl;
}