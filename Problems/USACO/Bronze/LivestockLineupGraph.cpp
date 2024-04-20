#include <iostream>
#include <vector>
#include <string>
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

    // for (pair<string, set<string> > p: must_adjacent) {
    //     printf("[%s]: ", p.first.c_str());
    //     for (string s: p.second) {
    //         cout << s << " ";
    //     }
    //     cout << endl;
    // }

    set<string> used;
    vector<string> ordering;

    for (int i = 0; i < (int) cows.size(); i++) {
        if (used.count(cows[i])) continue;

        if ((int) must_adjacent[cows[i]].size() <= 1) {
            ordering.push_back(cows[i]);
            used.insert(cows[i]);
        }
        
        if ((int) must_adjacent[cows[i]].size() == 1) {
            string current = *must_adjacent[cows[i]].begin();
            ordering.push_back(current);
            used.insert(current);

            while ((int) must_adjacent[current].size() == 2) {
                auto it = must_adjacent[current].begin();
                string cow_a = *it;
                it++; string cow_b = *it;

                string next = cow_a;
                if (used.count(cow_a)) {
                    next = cow_b;
                }

                ordering.push_back(next);
                used.insert(next);
                current = next;
            }
        }
    }

    for (int i = 0; i < (int) ordering.size(); i++) {
        cout << ordering[i] << endl;
    }
}