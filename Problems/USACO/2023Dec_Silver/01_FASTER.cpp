#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <vector>

typedef long long i64;

using namespace std;

int main(void) {
    i64 N, M, K;
    cin >> N >> M >> K;

    map<i64, i64> weights;
    for (i64 i = 0; i < N; i++) {
        i64 w, a;
        cin >> w >> a;
        weights[w] = a;
    }

    map<i64, i64> weights_save = weights;

    // lowers of length [key] contain [value] many groups
    map<i64, i64> towers;
    vector<vector<i64> > groups;

    while (!weights.empty()) {
        auto front = weights.begin(); 
        vector<i64> this_group;

        while (front != weights.end()) {
            this_group.push_back(front->first);
            auto next_front = weights.lower_bound(front->first + K);
            front = next_front;
        }

        for (i64 member: this_group) {
            weights.erase(member);
        }

        groups.push_back(this_group);
    }

    for (auto group: groups) {
        vector<i64> member_counts;
        for (i64 member: group) {
            member_counts.push_back(weights_save[member]);
        }

        sort(member_counts.begin(), member_counts.end());

        i64 taken = 0;
        i64 max_group_size = group.size();

        for (i64 count: member_counts) {
            count -= taken;
            taken += count;

            towers[max_group_size] += count;
            max_group_size--;
        }
    }

    i64 n_cows = 0;
    i64 n_towers_remaining = M;

    for (auto it = towers.rbegin(); it != towers.rend(); it++) {
        // printf("%lld => %lld\n", it->first, it->second);

        i64 towers_put = min(it->second, n_towers_remaining);
        n_cows += towers_put * it->first;
        n_towers_remaining -= towers_put;
    }

    cout << n_cows << endl;
}