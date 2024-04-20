#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <numeric>
#include <vector>
#include <tuple>
#include <iomanip>

using namespace std;

int main(void) {
    vector<int> order(9);
    iota(order.begin(), order.end(), 0);

    vector<int> grid(9);
    for (int i = 0; i < 9; i++) {
        cin >> grid[i];
    }

    vector<tuple<int, int, int> > lines = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},

        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},

        {0, 4, 8},
        {2, 4, 6}
    };

    int all_cases = 0;
    int good_cases = 0;

    do {
        int bad_flag = false;
        all_cases++;

        for (auto line: lines) {
            // if it's seen in a bad order
            int a = get<0>(line);
            int b = get<1>(line);
            int c = get<2>(line);

            if (grid[a] == grid[b] && order[c] > order[a] && order[c] > order[b]) {
                bad_flag = true;
            } 

            else
            if (grid[a] == grid[c] && order[b] > order[a] && order[b] > order[c]) {
                bad_flag = true;
            }

            else
            if (grid[b] == grid[c] && order[a] > order[b] && order[a] > order[c]) {
                bad_flag = true;
            }
        }

        if (!bad_flag) {
            good_cases++;
        }
    } while (next_permutation(order.begin(), order.end()));

    // cout << bad_cases << endl;
    cout.precision(10);
    cout << ((double) (good_cases) / (double) all_cases) << endl;
}