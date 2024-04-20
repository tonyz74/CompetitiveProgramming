#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
using i64 = long long;

i64 N, K;
vector<i64> years;
vector<i64> periods_with_cows;

i64 get_period(i64 yr) {
    if (yr % 12 == 0) {
        return yr / 12;
    }
    return yr / 12 + 1;
}

int main(void) {
    cin >> N >> K;
    years.resize(N);


    set<i64, greater<i64> > dup_removal;
    for (i64 i = 0; i < N; i++) {
        cin >> years[i];
        dup_removal.insert(get_period(years[i]));
    }

    for (auto p: dup_removal) {
        periods_with_cows.push_back(p);
    }

    i64 answer = periods_with_cows[0] * 12;
    
    i64 n_periods = (i64) periods_with_cows.size();
    vector<i64> pairwise_diff(n_periods, 0);
    for (i64 i = 0; i < n_periods - 1; i++) {
        pairwise_diff[i] = (periods_with_cows[i] - 1) - periods_with_cows[i + 1];
    }
    pairwise_diff[n_periods - 1] = periods_with_cows[n_periods - 1] - 1;

    std::sort(pairwise_diff.begin(), pairwise_diff.end());
    std::reverse(pairwise_diff.begin(), pairwise_diff.end());

    // we use one for jumping to the earliest past
    i64 jumps_left = K - 1;
    for (i64 k = 0; k < min(jumps_left, (i64) pairwise_diff.size()); k++) {
        answer -= 12 * pairwise_diff[k];
    }

    printf("%lld\n", answer);
}