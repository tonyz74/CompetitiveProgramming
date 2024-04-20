#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

void solve() {
    int N;
    cin >> N;

    vector<int> ordering;
    ordering.reserve(N + 1);
    stack<int> to_sell;

    // animal i -> every animal afraid of that animal i
    unordered_map<int, int> num_afraid_of_me;

    vector<bool> sold(N + 1, false);

    vector<int> afraid_of(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> afraid_of[i];
        num_afraid_of_me[afraid_of[i]]++;
    }

    vector<int> costs(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        cin >> costs[i];
    }

    for (int i = 1; i <= N; i++) {
        if (num_afraid_of_me[i] == 0) {
            to_sell.push(i);
        }
    }

    while (!to_sell.empty()) {
        int animal = to_sell.top();
        to_sell.pop();
        sold[animal] = true;
        ordering.push_back(animal);

        int next = afraid_of[animal];
        num_afraid_of_me[next]--;

        if (num_afraid_of_me[next] == 0) {
            to_sell.push(next);
        }
    }

    // for (int i = 0; i < ordering.size(); i++) {
    //     printf("%d ", ordering[i]);
    // }
    // printf("\n");

    for (int a = 1; a <= N; a++) {
        if (!sold[a]) {
            // printf("trying to sell the cycle with %d in it\n", a);
            // find the minimum, then find the one it's connected to,
            // then sell from there (so we don't get double price only for the min)

            int min_cost = costs[a];
            int min_animal = a;
            int iter = afraid_of[a];

            while (iter != a) {
                if (costs[iter] < min_cost) {
                    min_cost = costs[iter];
                    min_animal = iter;
                }
                iter = afraid_of[iter];
            }

            // sell this one last, so sell the one it's afraid of first
            iter = afraid_of[min_animal];
            int one_after = afraid_of[min_animal];
            do {
                ordering.push_back(iter);
                sold[iter] = true;
                iter = afraid_of[iter];
            } while (iter != one_after);
        }
    }

    for (int i = 0; i < ordering.size(); i++) {
        printf("%d ", ordering[i]);
    }
    printf("\n");
}

int main(void) {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        solve();
    }
}