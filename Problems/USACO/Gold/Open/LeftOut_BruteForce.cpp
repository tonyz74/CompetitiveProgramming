#include <iostream>
#include <vector>
#include <string>

using namespace std;

int grid[1002][1002];

void setIO() {
    #ifndef TZ74_LOCAL_TESTING
    freopen("leftout.in", "r", stdin);
    freopen("leftout.out", "w", stdout);
    #endif
}

bool check(int N) {
    int good = 1;

    for (int i = 2; i <= N; i++) {
        int n_equal = 0;
        for (int j = 1; j <= N; j++) {
            if (grid[i - 1][j] == grid[i][j]) n_equal++;
        }

        if (n_equal == 0 || n_equal == N) {
            good++;
        }
    }

    return good == N;
}

int main(void) {
    setIO();
    int N; cin >> N;

    for (int i = 1; i <= N; i++) {
        string S; cin >> S;
        for (int j = 1; j <= N; j++) {
            grid[i][j] = S[j - 1] == 'R';
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            grid[i][j] ^= 1;
            bool res = check(N);
            grid[i][j] ^= 1;

            if (res) {
                printf("%d %d\n", i, j);
                return 0;
            }
        }
    }

    printf("-1\n");
}