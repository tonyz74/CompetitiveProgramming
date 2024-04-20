#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main(void) {
    int n; cin >> n;
    vector<long long> p(n); for (int i = 0; i < n; i++) cin >> p[i];

    long long min_diff = 1e9;

    for (int p1_n = 0; p1_n <= 10; p1_n++) {
        vector<bool> choices(n, 0);
        for (int i = 0; i < p1_n; i++) choices[i] = 1;
        reverse(choices.begin(), choices.end());

        do {
            long long p1_wt = 0;
            long long p2_wt = 0;
            for (int i = 0; i < n; i++) {
                if (choices[i]) p1_wt += p[i];
                else p2_wt += p[i];
            }

            min_diff = min(min_diff, abs(p2_wt - p1_wt));
        } while (next_permutation(choices.begin(), choices.end()));
    }

    cout << min_diff << endl;
}