#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int main(void) {
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);

    vector<string> cows = {
        "Bessie", "Buttercup", "Belinda",
        "Beatrice", "Bella", "Blue", "Betsy", "Sue"
    };
    sort(cows.begin(), cows.end());

    int N; cin >> N;
    map<string, set<string>> must_adjacent;

    for (int i = 0; i < N; i++) {
        string cow1, tmp, cow2;
        cin >> cow1 >> tmp >> tmp >> tmp >> tmp >> cow2;
        // cout << cow1 << " " << cow2 << endl;

        must_adjacent[cow1].insert(cow2);
        must_adjacent[cow2].insert(cow1);
    }

    vector<string> valid_ordering;
    do {
        for (int i = 0; i < 8; i++) {
            for (string adj: must_adjacent[cows[i]]) {
                if ((i - 1 >= 0 && cows[i - 1] == adj) ||
                    (i + 1 <= 7 && cows[i + 1] == adj)) {
                    (void) 0;
                } else {
                    goto ordering_fail;
                }
            }
        }

        valid_ordering = cows;
        break;

        ordering_fail: (void) 1;
    } while (next_permutation(cows.begin(), cows.end()));

    for (int i = 0; i < 8; i++) {
        cout << valid_ordering[i] << endl;
    }
}