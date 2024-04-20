#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define ODD 1
#define EVEN 0

void solve() {
    int N, M, K; cin >> N >> M >> K;
    vector<vector<int> > moves(M + 1, vector<int>(K + 1, 0));

    // loss when 1 => max loss if i play odd, loss when 0 => max loss if i play even
    vector<vector<int> > worst_case(M + 1, vector<int>(2, 0));
    vector<int> best_to(M + 2, 0);

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= K; j++) {
            cin >> moves[i][j];
        }
    }

    for (int i = 1; i <= M; i++) {
        int min_odd = 1e9;
        int max_odd = 0;
        int min_even = 1e9;
        int max_even = 0;

        for (int j = 1; j <= K; j++) {
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
            worst_case[i][EVEN] = -max_odd;
            worst_case[i][ODD] = min_odd;
        }

        // there were no odds 
        else if (min_odd == 1e9) {
            worst_case[i][ODD] = -max_even;
            worst_case[i][EVEN] = min_even;
        }

        // both exist
        else {
            worst_case[i][ODD] = -max_even;
            worst_case[i][EVEN] = -max_odd;
        }
    }

    vector<int> sfx_min(M + 2, 1e9);
    for (int i = 1; i <= M; i++) {
        best_to[i] = best_to[i - 1] + max(worst_case[i][0], worst_case[i][1]);
    }
    for (int i = M; i >= 1; i--) {
        sfx_min[i] = min(sfx_min[i + 1], best_to[i]);
    }
    // for (int i = 1; i <= M; i++) {
    //     printf("%d ", best_to[i]);
    // }
    // printf("\n");

    // for (int i = 1; i <= M; i++) {
    //     printf("%d ", sfx_min[i]);
    // }
    // printf("\n");

    // even the best moves result in 0 or below, fail
    if (N + sfx_min[1] <= 0) {
        printf("-1\n");
        return;
    }

    int now = N;
    vector<int> strat;

    // if picking even here causes our future to dip below 0, we
    // must pick odd, else we just pick even
    for (int i = 1; i <= M; i++) {
        int with_pick_even = now + worst_case[i][EVEN];

        if (with_pick_even + (sfx_min[i] - best_to[i]) > 0) {
            strat.push_back(0);
            now = with_pick_even;
        } else {
            strat.push_back(1);
            now = now + worst_case[i][ODD];
        }

    }

    assert((int) strat.size() == (int) M);
    int tot = N;
    for (int m = 0; m < (int) (strat.size()); m++) {
        if (strat[m] == 0) printf("Even");
        else printf("Odd");

        tot += worst_case[m + 1][strat[m]];
        assert(tot > 0);

        if (m != (int) (strat.size() - 1)) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}