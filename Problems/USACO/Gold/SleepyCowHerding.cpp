#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

using i64 = long long;

int N;

i64 calc_min_moves(const vector<i64>& cows) {
    // special cases: all cows consecutive, one far, cannot insert
    // into already filled spaces so too bad
    if (cows[N - 2] - cows[0] == (N - 2) && (cows[N - 1] - cows[N - 2]) > 2) {
        return 2;
    }
    if (cows[N - 1] - cows[1] == (N - 2) && (cows[1] - cows[0]) > 2) {
        return 2;
    }

    i64 max_block = 0;

    // i to j inclusive
    i64 j = 0;
    for (i64 i = 0; i < N; i++) {
        // if the next cow's distance to this cow is still less than N,
        // keep going. otherwise stop. if the next cow's is equal to N
        // we don't want that either; N units away means N + 1 total.

        while (j < N - 1 && cows[j + 1] - cows[i] < N) {
            j++;
        }

        max_block = max(max_block, (j - i + 1));
    }

    return N - max_block;
}

int main(void) {
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    cin >> N;
    vector<i64> cows;  

    for (int i = 0; i < N; i++) {
        int ci;
        cin >> ci;
        cows.push_back(ci);
    }
    std::sort(cows.begin(), cows.end());

    // first do minimum
    cout << calc_min_moves(cows) << endl;

    i64 moves = max(
        (cows[N - 1] - cows[1]),
        (cows[N - 2] - cows[0])
    ) - 1 - (N - 3);
    
    // max finds biggest difference, -1 because we start off moving
    // into one block in that difference, (N - 3) for number of cows
    // we can disregard (two endpoints + the "crutch")

    cout << moves << endl;
}