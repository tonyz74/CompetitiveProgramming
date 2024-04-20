#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

#define state_cout() state[1] << " " << state[2] << " " << state[3] << " "

struct iter {
    int x, y, g;
};

void setIO() {
    freopen("shell.in", "r", stdin);
    freopen("shell.out", "w,", stdout);
}

int main(void) {
    setIO();

    int N; cin >> N;
    vector<iter> moves(N);
    for (int i = 0; i < N; i++) cin >> moves[i].x >> moves[i].y >> moves[i].g;
    
    int best = 0;

    for (int start = 1; start <= 3; start++) {
        int state[4] = {0};
        state[start] = 1;

        int score = 0;
    
        for (int i = 0; i < (int) moves.size(); i++) {
            int tmp = state[moves[i].x];
            state[moves[i].x] = state[moves[i].y];
            state[moves[i].y] = tmp;
            score += (state[moves[i].g] == 1);
        }

        best = max(score, best);
    }

    cout << best << endl;
}