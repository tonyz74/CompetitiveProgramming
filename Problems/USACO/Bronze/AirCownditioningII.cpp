#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

struct cow {
    int start, end;
    int cool_req;
};

struct aircon {
    int start, end;
    int cooling;
    int cost;
};

int main(void) {
    int N, M; cin >> N >> M;

    vector<cow> cows(N);
    for (int i = 0; i < N; i++) {
        cin >> cows[i].start >> cows[i].end >> cows[i].cool_req;
        cows[i].start--;
        cows[i].end--;
    }

    int buy_all = 0;
    vector<aircon> ac(M);
    for (int m = 0; m < M; m++) {
        cin >> ac[m].start >> ac[m].end >> ac[m].cooling >> ac[m].cost;
        ac[m].start--;
        ac[m].end--;
        buy_all += ac[m].cost;
    }

    vector<int> req_cooling(100, 0);
    for (int i = 0; i < N; i++) {
        for (int j = cows[i].start; j <= cows[i].end; j++) {
            req_cooling[j] = max(req_cooling[j], cows[i].cool_req);
        }
    }

    int best_price = 1e9;
    for (int aircons_used = 0; aircons_used <= M; aircons_used++) {
        vector<int> choose(M, 0);

        for (int i = 0; i < aircons_used; i++) {
            choose[i] = 1;
        }
        sort(choose.begin(), choose.end());

        do {
            int this_price = 0;
            vector<int> state(100, 0);

            for (int i = 0; i < M; i++) {
                if (choose[i] == 0) continue;

                this_price += ac[i].cost;
                // printf("adding %d (i = %d)\n", ac[i].cost, i);
                for (int p = ac[i].start; p <= ac[i].end; p++) {
                    state[p] += ac[i].cooling;
                }
            }

            for (int i = 0; i < 100; i++) {
                if (state[i] < req_cooling[i]) goto failed_config;
            }

            best_price = min(best_price, this_price);

            failed_config: (void) 1;
        } while (next_permutation(choose.begin(), choose.end()));
    }

    if (best_price == 1e9) {
        printf("%d\n", buy_all);
    } else {
        printf("%d\n", best_price);
    }
}