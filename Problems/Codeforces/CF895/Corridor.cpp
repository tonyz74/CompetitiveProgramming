#include <iostream>
#include <vector>

using namespace std;

void solve(void) {
    int N;
    cin >> N;
    vector<pair<int, int>> traps(N);

    // printf("\n\ntest case:\n");

    for (int i = 0; i < N; i++) {
        int pos, delay;
        cin >> pos >> delay;
        traps[i] = make_pair(pos, delay);
    }

    // sort(traps.begin(), traps.end());

    int best_k = 1e9;

    for (int i = 0; i < N; i++) {
        int getting_over = traps[i].first - 1;
        int activation_time = getting_over + traps[i].second;

        // printf("activation: %d, i = %d\n", activation_time, i);

        best_k = min(
            best_k,
            traps[i].first + (traps[i].second - 1) / 2
        );
    }

    printf("%d\n", best_k);
}

int main(void) {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) solve();
}