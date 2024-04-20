#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using i64 = long long;

struct ht {
    i64 value;
    i64 index; 

    ht() {}
    ht(i64 v, i64 i): value(v), index(i) {}

    bool operator<(const ht& rhs) const {
        return make_pair(index, value) < make_pair(rhs.index, rhs.value);
    }
};

bool sort_by_value_decreasing(const ht& lhs, const ht& rhs) {
    return lhs.value > rhs.value;
}

i64 solve(const vector<i64>& heights) {
    i64 ans = 0;
    i64 N = heights.size();

    vector<ht> dup(N);
    for (i64 i = 0; i < N; i++) {
        dup[i] = ht(heights[i], i);
    }
    std::sort(dup.begin(), dup.end(), sort_by_value_decreasing);

    set<ht> sh;
    for (int i = 0; i < N; i++) {
        ht curr = dup[i];
        auto [it, success] = sh.insert(curr);

        it++;
        if (it != sh.end()) {
            ans += (it->index - curr.index + 1);
        }
    }

    return ans;
}

int main(void) {
    i64 N; cin >> N;
    vector<i64> H(N);
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }

    i64 ans = solve(H);
    std::reverse(H.begin(), H.end());
    ans += solve(H);

    cout << ans << endl;
}