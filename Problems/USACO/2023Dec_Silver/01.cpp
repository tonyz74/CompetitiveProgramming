#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long i64;

int main(void) {
    i64 N, M, K;
    cin >> N >> M >> K;

    map<i64, i64> weights;
    for (i64 i = 0; i < N; i++) {
        i64 w, a;
        cin >> w >> a;
        weights[w] = a;
    }

    // start at the back
    i64 n_towers_made = 0;
    i64 cows_used = 0;

    // lowers of length [key] contain [value] many cows
    map<i64, i64> towers;

    // make as many towers as possible
    while (true && !weights.empty()) {
        i64 taken = 1e18;
        i64 n_towers_left = M - n_towers_made;

        if (n_towers_left == 0) break;

        vector<i64> weights_used;

        auto front = weights.begin();

        while (front != weights.end()) {
            weights_used.push_back(front->first);
            taken = min(taken, min(n_towers_left, front->second));

            auto next_front = weights.lower_bound(front->first + K);
            front = next_front;
        }

        // printf("%lldx: ", taken);
        for (i64 x: weights_used) {
            cows_used += taken;
            weights[x] -= taken;
            if (weights[x] == 0) weights.erase(x);
            // printf("%lld ", x);
        }
        // printf("\n");

        if (taken == 0 || taken == 1e18) break;

        n_towers_made += taken;
    }

    printf("%lld\n", cows_used);
}