#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int N, M, K; cin >> N >> M >> K;
    vector<vector<int> > moves(M + 1, vector<int>(K + 1, 0));
    vector<vector<int> > worst_case(M + 1, vector<int>(2, 0));

    for (int i = 1; i <= M; i++) {
        int min_even = 1e9;
        int min_odd = 1e9;
        int max_even = 0;
        int max_odd = 0;

        for (int j = 1; j <= K; j++) {
            cin >> moves[i][j];

            if (moves[i][j] % 2 == 0) {
                min_even = min(min_even, moves[i][j]);
                max_even = max(max_even, moves[i][j]);
            } else {
                min_odd = min(min_odd, moves[i][j]);
                max_odd = max(max_odd, moves[i][j]);
            }
        }

        // there were no evens
        if (min_even == 1e9) {
            worst_case[i][0] = -max_odd;
            worst_case[i][1] = min_odd;
        }

        // there were no odds 
        else if (min_odd == 1e9) {
            worst_case[i][1] = -max_even;
            worst_case[i][0] = min_even;
        }

        // both exist
        else {
            worst_case[i][1] = -max_even;
            worst_case[i][0] = -max_odd;
        }

        // printf("%d %d\n", worst_case[i][0], worst_case[i][1]);
    }

    int seq = -1;
    for (int test_seq = 0; test_seq <= ((1 << M) - 1); test_seq++) {
        // int test_seq = 0b01101;

        int tot = N;
        int j = 1;
        int ok = true;

        for (int i = M - 1; i >= 0; i--) {
            int val_at_i = (bool) (test_seq & (1 << (i)));
            tot += worst_case[j][val_at_i];
            // printf("worst case: %d, val: %d\n", worst_case[j][val_at_i], val_at_i);

            if (tot <= 0) {
                ok = false;
                break;
            }

            j++;
        }

        if (ok) {
            // printf("ok\n");
            seq = test_seq;
            break;
            // return;
        }

    }

    if (seq == -1) printf("-1\n");
    else {

        for (int x = M - 1; x >= 0; x--) {
            if (seq & (1 << x)) {
                printf("Odd");
            } else {
                printf("Even");
            }

            if (x == 0) printf("\n");
            else printf(" ");
        }

    }
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}