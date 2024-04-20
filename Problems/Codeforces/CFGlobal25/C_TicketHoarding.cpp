#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using i64 = long long;

struct take {
    i64 value;
    i64 quantity;

    bool operator<(const take& rhs) const {
        return value < rhs.value;
    }
};

void solve() {
    i64 N, M, K; cin >> N >> M >> K;
    vector<i64> A(N + 1);
    for (i64 i = 1; i <= N; i++) cin >> A[i];

    std::sort(A.begin() + 1, A.end());
    i64 rem = K;
    i64 cost = 0;

    for (i64 i = 1; i <= N; i++) {
        i64 to_take = min(rem, M);
        cost += to_take * A[i];
        rem -= to_take;
    }

    rem = K;
    i64 accum = 0;
    for (i64 i = 1; i <= N; i++) {
        i64 to_take = min(rem, M);
        cost += to_take * accum;
        accum += to_take;
        rem -= to_take;
    }

    cout << cost << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}