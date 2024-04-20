#include <iostream>
#include <deque>
#include <string>

using namespace std;
#define PLAYER 'P'
#define EMPTY '.'
#define WALL '#'

int N;
int dist[61][61][61][61];
int grid[61][61];

struct pos {
    int i, j;
    pos() {}
    pos(int row, int col) : i(row), j(col) {}
};

struct iter {
    pos p1, p2;
    int dist;

    iter(pos first, pos second, int d) : p1(first), p2(second), dist(d) {}
};

pos attempt_move(pos orig, pair<int, int> shift) {
    pos new_pos = orig;
    new_pos.i += shift.first;
    new_pos.j += shift.second;

    if (new_pos.i <= 0 || new_pos.i > N || new_pos.j <= 0 || new_pos.j > N) {
        return orig;
    } else if (grid[new_pos.i][new_pos.j] == WALL) {
        return orig;
    }

    return new_pos;
}

void search(pos p1_pos, pos p2_pos) {    
    deque<iter> dq;
    dq.push_back(iter(p1_pos, p2_pos, 0));

    while (!dq.empty()) {
        iter top = dq.front();
        dq.pop_front();
        if (dist[top.p1.i][top.p1.j][top.p2.i][top.p2.j] != 1e9) continue;
        dist[top.p1.i][top.p1.j][top.p2.i][top.p2.j] = top.dist;

        vector<pair<int, int> > moves = {
            { -1, 0 },
            { 1, 0 },
            { 0, 1 },
            { 0, -1 }
        };

        for (auto mov: moves) {
            pos new_p1 = attempt_move(top.p1, mov);
            pos new_p2 = attempt_move(top.p2, mov);

            if (dist[new_p1.i][new_p1.j][new_p2.i][new_p2.j] == 1e9) {
                dq.push_back(iter(new_p1, new_p2, top.dist + 1));
            }
        }
    }
}

#define F0R(_vname, _start, _end) for (int _vname = _start; _vname <= _end; _vname++)

int main(void) {
    F0R(i, 0, 60) F0R(j, 0, 60) F0R(k, 0, 60) F0R(l, 0, 60) {
        dist[i][j][k][l] = 1e9;
    }

    cin >> N;
    pos p1_pos = pos(-1, -1);
    pos p2_pos = pos(-1, -1);

    for (int i = 1; i <= N; i++) {
        string S; cin >> S;
        for (int j = 1; j <= N; j++) {
            if (S[j - 1] == PLAYER) {
                if (p1_pos.i == -1) {
                    p1_pos = pos(i, j);
                } else {
                    p2_pos = pos(i, j);
                }
                S[j - 1] = EMPTY;
            }
            grid[i][j] = S[j - 1];
        }
    }

    search(p1_pos, p2_pos);

    int ans = 1e9;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            ans = min(ans, dist[i][j][i][j]);
        }
    }
    
    if (ans == 1e9) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
}