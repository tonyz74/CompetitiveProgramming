#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

using i64 = long long;
using p = pair<i64, i64>;

struct reg {
    i64 L;
    i64 R;

    bool operator<(const reg& rhs) const {
        return make_pair(R, L) < make_pair(rhs.R, rhs.L);
    }
};

void solve() {
    i64 N; cin >> N;
    vector<reg> regs(N);
    for (i64 i = 0; i < N; i++) {
        cin >> regs[i].L >> regs[i].R;
    }
    std::sort(regs.begin(), regs.end());

    set<i64> free_spaces;
    for (i64 i = 0; i < N; i++) {
        free_spaces.insert(regs[i].L);
    } 

    set<i64> filled;

    // already sorted in non-decreasing order of right endpoint
    for (i64 i = 0; i < N; i++) {
        // try to put at L
        i64 next_free = *free_spaces.lower_bound(regs[i].L);

        if (next_free > regs[i].R) {
            printf("No\n");
            return;
        }

        // printf("put %lld at %lld\n", i, next_free);

        free_spaces.erase(next_free);
        filled.insert(next_free);

        if (!filled.count(next_free + 1)) {
            free_spaces.insert(next_free + 1);
        }
    }

    printf("Yes\n");
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
}