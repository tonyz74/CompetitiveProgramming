#include <iostream>
#include <vector>
#include <string>

using namespace std;

int grid[1002][1002];
int n_eq_above[1002];

void setIO() {
    #ifndef TZ74_LOCAL_TESTING
    freopen("leftout.in", "r", stdin);
    freopen("leftout.out", "w", stdout);
    #endif
}

int main(void) {
    setIO();
    int N; cin >> N;

    auto is_ok = [&] (int x) {
        return x == 0 || x == N;
    };

    for (int i = 1; i <= N; i++) {
        string S; cin >> S;
        for (int j = 1; j <= N; j++) {
            grid[i][j] = S[j - 1] == 'R';

            if (i >= 2) {
                n_eq_above[i] += grid[i][j] == grid[i - 1][j];
            }
        }
    }

    int ok_rows = 0;
    for (int i = 1; i <= N; i++) {
        // printf("row: %d => %d\n", i, n_eq_above[i]);
        ok_rows += is_ok(n_eq_above[i]);
    }

    if (ok_rows == N) {
        printf("-1\n");
        return 0;
    }

    auto get_res = [&] (int i, int j) {
        int cpy_a = n_eq_above[i];
        int cpy_b = n_eq_above[i + 1];

        if (i >= 2) {
            if (grid[i - 1][j] == grid[i][j]) {
                cpy_a++;
            } else {
                cpy_a--;
            }
        } else {
            cpy_a = -1;
        }

        if (i <= N - 1) {
            if (grid[i + 1][j] == grid[i][j]) {
                cpy_b++;
            } else {
                cpy_b--;
            }
        } else {
            cpy_b = -1;
        }

        return make_pair(cpy_a, cpy_b);
    };

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // try to flip the (i, j) th bit
            grid[i][j] ^= 1;
            auto p = get_res(i, j);

            // printf("i: %d, j: %d;   p=%d,%d\n", i, j, p.first, p.second);

            int now = ok_rows;
            if (i >= 2) {
                now -= is_ok(n_eq_above[i]);
                now += is_ok(p.first);
            }

            if (i <= N - 1) {
                now -= is_ok(n_eq_above[i + 1]);
                now += is_ok(p.second);
            }

            if (now == N) {
                printf("%d %d\n", i, j);
                return 0;
            }

            grid[i][j] ^= 1;
        }
    }

    printf("-1\n");
}