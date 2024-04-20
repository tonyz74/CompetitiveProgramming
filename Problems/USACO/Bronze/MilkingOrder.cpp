#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool in_vec(const vector<int>& v, int x) {
    for (int i = 0; i < (int) v.size(); i++) {
        if (v[i] == x) return true;
    }
    return false;
}

int N, M, K;
vector<int> relative;

bool is_valid_config(const vector<int>& order_ref) {
    vector<int> order = order_ref;
    vector<int> cow_to_pos(N + 1, -1);

    for (int i = 1; i <= N; i++) {
        if (order[i] != -1) {
            cow_to_pos[order[i]] = i;
        }
    }

    int min_pos = 1;
    for (int rel_i = 0; rel_i < M; rel_i++) {
        if (cow_to_pos[relative[rel_i]] != -1) {
            int existing_pos = cow_to_pos[relative[rel_i]];

            if (existing_pos < min_pos) {
                return false;
            }

            // skip placing this cow
            min_pos = existing_pos;
            continue;
        }

        // find the next free spot
        while (order[min_pos] != -1) {
            min_pos++;

            // trying to place past end of array, we cannot
            if (min_pos > N) {
                return false;
            }
        }

        order[min_pos] = relative[rel_i];
        cow_to_pos[relative[rel_i]] = min_pos;
    }

    return true;
}

int main(void) {
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);
    
    cin >> N >> M >> K;
    relative.resize(M);

    vector<int> specific(N + 1, -1);
    vector<int> base_order(N + 1, -1);

    for (int i = 0; i < M; i++) {
        cin >> relative[i];
    }

    for (int i = 0; i < K; i++) {
        int c, p; cin >> c >> p;
        base_order[p] = c;
        specific[c] = p;

        // it's fixed in place, after all
        if (c == 1) {
            printf("%d\n", p);
            return 0;
        }
    }

    for (int cow1_pos = 1; cow1_pos <= N; cow1_pos++) {
        if (base_order[cow1_pos] != -1) continue;

        base_order[cow1_pos] = 1;

        if (is_valid_config(base_order)) {
            cout << cow1_pos << endl;
            return 0;
        }

        base_order[cow1_pos] = -1;
    }
}