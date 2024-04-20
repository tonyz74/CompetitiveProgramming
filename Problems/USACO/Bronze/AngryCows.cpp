#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main(void) {
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    int N; cin >> N;
    vector<int> X(N);

    for (int i = 0; i < N; i++) cin >> X[i];

    int max_detonate = 0;

    for (int hay = 0; hay < N; hay++) {
        int hay_pos = X[hay];
        // landing on this bale first. How many can I detonate?

        int detonated = 1;
        set<pair<int, int> > bales_right;
        set<pair<int, int> > bales_left;

        for (int i = 0; i < N; i++) {
            if (i == hay) continue;

            int diff = X[i] - hay_pos;
            if (diff < 0) bales_left.insert(make_pair(-diff, X[i]));
            else bales_right.insert(make_pair(diff, X[i]));
        }

        // simulate
        int range = 1, k = 2;
        for (auto it = bales_left.begin(); it != bales_left.end(); it++) {
            auto next = it; next++;

            if (it->first <= range) {
                detonated++;
                if (next == bales_left.end() || next->first > range) {
                    range = it->first + k;
                    // printf("blew up %d (range is now %d)\n", it->second, range);
                    k++;
                }
            } else {
                break;
            }
        }

        range = 1; k = 2;
        for (auto it = bales_right.begin(); it != bales_right.end(); it++) {
            auto next = it; next++;

            if (it->first <= range) {
                detonated++;
                if (next == bales_right.end() || next->first > range) {
                    range = it->first + k;
                    // printf("blew up %d (range is now %d)\n", it->second, range);
                    k++;
                }
            } else {
                break;
            }
        }

        // printf("detonated at landing at %d is %d\n", hay_pos, detonated);
        max_detonate = max(max_detonate, detonated);
    }

    cout << max_detonate << endl;
}