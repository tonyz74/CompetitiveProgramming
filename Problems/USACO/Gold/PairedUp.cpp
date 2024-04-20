#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

using p = pair<i64, i64>;

int main(void) {
    freopen("pairup.in", "r", stdin);
    freopen("pairup.out", "w", stdout);

    i64 N; cin >> N;
    vector<p> cows(N);

    for (int i = 0; i < N; i++) {
        cin >> cows[i].second >> cows[i].first;
    } 

    std::sort(cows.begin(), cows.end());

    int L = 0;
    int R = N - 1;

    i64 max_time = 0;

    while (L < R) {
        i64 to_take = min(cows[R].second, cows[L].second);
        max_time = max(max_time, cows[R].first + cows[L].first);

        cows[R].second -= to_take;
        cows[L].second -= to_take;

        if (cows[R].second == 0) R--;
        if (cows[L].second == 0) L++;
    }

    cout << max_time << endl;
}