#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct meet {
    int t, x, y;

    bool operator<(const meet& rhs) const {
        return this->t < rhs.t;
    }
};

int main(void) {
    freopen("tracing.in", "r", stdin);
    freopen("tracing.out", "w", stdout);
    
    int N, T; cin >> N >> T;
    string state_str; cin >> state_str;

    vector<bool> state;
    state.push_back(0);
    for (int i = 0; i < N; i++) state.push_back(state_str[i] == '1');
    
    vector<meet> meets(T + 1);
    for (int i = 1; i <= T; i++) {
        cin >> meets[i].t >> meets[i].x >> meets[i].y;
    }

    sort(meets.begin() + 1, meets.end());

    int valid_cows = 0;
    int max_k = 0;
    int min_k = 1e9;

    for (int sc = 1; sc <= N; sc++) {
        bool ok = false;
        int K = 0;

        for (; K <= T; K++) {
            vector<int> transmits_left(N + 1, 0);
            transmits_left[sc] = K;
            vector<bool> is_sick(N + 1, false);
            is_sick[sc] = true;

            // simulate all the events
            for (int meet = 1; meet <= T; meet++) {
                int c1 = meets[meet].x;
                int c2 = meets[meet].y;

                // c1 infects c2
                int orig_c2 = is_sick[c2];
                if (is_sick[c1] && transmits_left[c1] != 0) {
                    transmits_left[c1]--;

                    if (!is_sick[c2]) {
                        transmits_left[c2] = K;
                        is_sick[c2] = true;
                    }
                }

                // c2 infects c1
                if (orig_c2 && transmits_left[c2] != 0) {
                    transmits_left[c2]--;

                    if (!is_sick[c1]) {
                        transmits_left[c1] = K;
                        is_sick[c1] = true;
                    }
                }

                // printf("c1 %d and c2 %d meet.\n", c1, c2);
                // for (int i = 1; i <= N; i++) {
                //     printf("%d ", transmits_left[i]);
                // }
                // printf("\n");
                // for (int i = 1; i <= N; i++) {
                //     printf("%d ", (int) is_sick[i]);
                // }
                // printf("\n");
            }

            for (int i = 1; i <= N; i++) {
                if (state[i] != is_sick[i]) {
                    goto not_this_k;
                }
            }

            min_k = min(min_k, K);
            max_k = max(max_k, K);

            ok = true;

            not_this_k: (void) 1;
        }

        // if at least one of them is possibly sick, ok
        if (ok != 0) {
            valid_cows++;
        }
    }

    cout << valid_cows << " " << min_k;
    if (max_k == T) {
        cout << " " << "Infinity";
    } else {
        cout << " " << max_k;
    }

    cout << endl;
}
