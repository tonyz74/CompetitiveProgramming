#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int max_all(const vector<int>& a) {
    int k = 0;
    for (int v: a) k = max(k, v);
    return k;
}

int main(void) {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);
    // int Q1, Q2, Q3, Q4;

    int N; cin >> N;
    vector<pair<int, int> > cows(N);

    vector<pair<int, int> > x_sorted;
    vector<pair<int, int> > y_sorted;

    x_sorted.push_back(make_pair(-1, -1));
    y_sorted.push_back(make_pair(-1, -1));

    for (int i = 0; i < N; i++) {
        cin >> cows[i].first >> cows[i].second;
        x_sorted.push_back(make_pair(cows[i].first, cows[i].second));
        y_sorted.push_back(make_pair(cows[i].second, cows[i].first));
    }

    sort(x_sorted.begin(), x_sorted.end());
    sort(y_sorted.begin(), y_sorted.end());

    int Q1 = 0, Q2 = 0, Q3 = 0, Q4 = 0;
    int best = 1e9;
    
    // above cow b_i, line: y = b
    for (int b_i = 0; b_i < (int) y_sorted.size(); b_i++) {
        // while the next one shares my y values, keep going up
        while (b_i + 1 < (int) y_sorted.size() && y_sorted[b_i + 1].first == y_sorted[b_i].first) {
            b_i++;
        }

        int height = y_sorted[b_i].first + 1;

        Q2 = 0; Q3 = 0;
        Q1 = N - b_i;
        Q4 = b_i;
        // printf("start: %d %d %d %d\n", Q1, Q2, Q3, Q4);

        best = min(best, max_all({Q1, Q2, Q3, Q4}));

        // line: x = a
        for (int a_i = 1; a_i < (int) x_sorted.size(); a_i++) {
            // add this current one to appropriate quadrant
            if (x_sorted[a_i].second < height) {
                Q4--;
                Q3++;
            } else {
                Q1--;
                Q2++;
            }

            bool can_upd = x_sorted[a_i].first != x_sorted[a_i + 1].first;
            // printf("a_i = %d, val = (%d, %d), quadrants: %d %d %d %d, can = %d\n", a_i, x_sorted[a_i].first, x_sorted[a_i].second, Q1, Q2, Q3, Q4, can_upd);


            if (can_upd) {
                best = min(best, max_all({Q1, Q2, Q3, Q4}));
            }
        }

    }

    cout << best << endl;
}