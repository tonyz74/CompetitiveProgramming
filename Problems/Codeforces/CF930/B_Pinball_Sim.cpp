#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define LEFT -1
#define RIGHT 1

using i64 = long long;

struct block {
    int dir = 0;
    int len = 1;
};

void solve() {
    int N; cin >> N;
    string S; cin >> S;
    S = "." + S;

    vector<block> pins(N + 1);
    for (int i = 1; i <= N; i++) {
        pins[i].dir = S[i] == '<' ? LEFT : RIGHT;
        pins[i].len = 1;
    }

    for (int start = 1; start <= N; start++) {
        block us = pins[start];
        int L = start;
        int R = start;

        i64 ops = 0;
        while (L > 0 && R < N + 1) {
            ops += us.len;

            if (us.dir == -1) {
                L--;

                // just in the same direction
                while (pins[L].dir == -1 && L > 0) {
                    ops++; us.len++;
                    L--;
                }

                // stop if we've exited
                if (L == 0) break;

                // otherwise somebody has joined us, originally
                // in the other direction, that can be handled
                // in the next iteration

                us.len++;
                us.dir = 1;

            } else {
                R++;

                // just in same dir
                while (pins[R].dir == 1 && R < N + 1) {
                    ops++; us.len++;
                    R++;
                }

                if (R == N + 1) break;

                // printf("hit right %d at ops = %lld\n", R, ops);
                us.len++;
                us.dir = -1;
            }
        }

        printf("%lld ", ops);
    }
    printf("\n");
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}