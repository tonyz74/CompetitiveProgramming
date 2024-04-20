#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int N; cin >> N;
    int M = N * 2;
    vector<int> w(M);
    for (int i = 0; i < M; i++) {
        cin >> w[i];
    }

    sort(w.begin(), w.end());

    // find the pair with the biggest difference then chuck them
    // into a single boat. sorted ones will be minimized by default.

    int best = 1e9;

    for (int x = 0; x < M; x++) {
        for (int y = x + 1; y < M; y++) {
            vector<int> dup;
            for (int i = 0; i < M; i++) {
                if (i != x && i != y) dup.push_back(w[i]);
            }

            int diff = 0;
            for (int i = 0; i < (int) dup.size() - 1; i += 2) {
                diff += dup[i + 1] - dup[i];
            }

            best = min(best, diff);
        }
    }

    printf("%d\n", best);
}