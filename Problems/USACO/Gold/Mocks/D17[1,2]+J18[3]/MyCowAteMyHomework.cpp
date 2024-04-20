#include <iostream>
#include <vector>
#include <cassert>
#include <map>

using namespace std;
using i64 = long long;

struct frac {
    i64 numer, denom;
    frac(i64 n, i64 d): numer(n), denom(d) {}

    bool operator<(const frac& rhs) const {
        return numer * rhs.denom < rhs.numer * denom;
    }
    bool operator==(const frac& rhs) const {
        return numer * rhs.denom == rhs.numer * denom;
    }
    bool operator>(const frac& rhs) const {
        return numer * rhs.denom > rhs.numer * denom;
    }
};

int main(void) {
    freopen("homework.in", "r", stdin);
    freopen("homework.out", "w", stdout);

    map<frac, vector<i64> > K_for_grade;

    i64 N; cin >> N;
    vector<i64> scores(N + 1);

    for (i64 i = 1; i <= N; i++) {
        cin >> scores[i];
    }

    vector<i64> sfx_sum(N + 2, 0);
    vector<i64> sfx_min(N + 2, 1e9);

    // stupid stupid stupid mistake (set sfx_sum[N] to 0, should be [N + 1])
    sfx_sum[N] = scores[N];
    sfx_min[N] = scores[N];
    // just do prefix sum from N to 1 for gods sake, just init N + 1
    for (i64 i = N - 1; i >= 1; i--) {
        sfx_sum[i] = scores[i] + sfx_sum[i + 1];
        sfx_min[i] = min(scores[i], sfx_min[i + 1]);
    }

    // for (int i = 1; i <= N; i++) {
    //     printf("%lld ", sfx_sum[i]);
    // }
    // printf("\n");
    // for (int i = 1; i <= N; i++) {
    //     printf("%lld ", sfx_min[i]);
    // }
    // printf("\n");

    // bessie ate up to K, meaning we only have K + 1 and afterwards available
    for (i64 K = 1; K <= N - 2; K++) {
        i64 rem_sum = sfx_sum[K + 1];
        i64 rem_min = sfx_min[K + 1];
        i64 rem_cnt = N - K;

        assert(rem_cnt >= 2);
        frac grade = frac(rem_sum - rem_min, rem_cnt - 1);
        K_for_grade[grade].push_back(K);
    }

    assert(K_for_grade.size() != 0);
    auto ptr = K_for_grade.rbegin(); 
    for (i64 x: ptr->second) {
        printf("%lld\n", x);
    }
}