#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

using grid = vector<string>;

grid rotate_90(const grid& in) {
    grid out = in;
    int n = in.size();

    // .*.      **.
    // *..  =>  ..* 
    // *.*  =>  *..
    for (int row = 0; row < n; row++) {
        out[row].resize(n);

        for (int col = 0; col < n; col++)
            out[col][n - 1 - row] = in[row][col];
    }

    return out;
}

void print_grid(const grid &g) {
    for (int i = 0; i < (int) g.size(); i++) {
        for (int j = 0; j < (int) g.size(); j++) {
            printf("%c", g[i][j]);
        }
        printf("\n");
    }
}

void solve() {
    int N; cin >> N;
    grid state;
    state.resize(N);
    for (int i = 0; i < N; i++) cin >> state[i];

    int K; cin >> K;
    grid orig_stamp(K);
    for (int i = 0; i < K; i++) cin >> orig_stamp[i];

    grid r90 = rotate_90(orig_stamp);
    grid r180 = rotate_90(r90);
    grid r270 = rotate_90(r180);
    set<grid> stamps_unq = {orig_stamp, r90, r180, r270};

    vector<vector<bool> > marked(N + 10, vector<bool>(N + 10, false));
    for (grid g: stamps_unq) {

        // print_grid(g);
        // try to fill the whole thing with this, if possible

        for (int r_off = 0; r_off < (N - K + 1); r_off++) {
            for (int c_off = 0; c_off < (N - K + 1); c_off++) {
                // printf("%d, %d\n", r_off, c_off);

                // mark if can fill this region
                int valid_stamp = true;
                for (int r = 0; r < K; r++) for (int c = 0; c < K; c++) {
                    if (state[r + r_off][c + c_off] == '.' && g[r][c] == '*') {
                        valid_stamp = false;
                        break;
                    }
                }

                // can do this stamp without touching a .
                if (valid_stamp) {
                    for (int r = 0; r < K; r++) for (int c = 0; c < K; c++) {
                        if (g[r][c] == '*') marked[r + r_off][c + c_off] = true;

                    }
                } else {
                    // printf("invalid at: %d %d\n", r_off, c_off);
                }

            }
        }
    }

    // printf("N is %d\n", N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            // printf("%d ", (int) marked[i][j]);

            // couldn't fill this one, but it's supposed to be filled
            if (marked[i][j] == 0 && state[i][j] == '*') {
                printf("NO\n");
                return;
            }
        }

        // printf("\n");
    }

    printf("YES\n");
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}