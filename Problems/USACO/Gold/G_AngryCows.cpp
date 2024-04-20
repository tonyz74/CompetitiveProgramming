#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

using i64 = long long;

i64 N;
vector<i64> X;
map<i64, i64> rmin_suffix;
map<i64, i64> rmin_prefix;

bool can_explode(i64 R) {
    (void) R;
    
    i64 i = 0;
    i64 j = 0;
    for (i = 0; i < N - 1; i++) {
        while (j != N - 1 && X[j + 1] - X[i] <= 2 * R) {
            j++;
        }

        // log_range(i, j);
        if (rmin_prefix[X[i]] <= R - 2 && rmin_suffix[X[j]] <= R - 2) {
            return true;
        }
    }

    // printf("\n[[pass 2]]:\n");
    // j = N - 1;
    // i = N - 1;
    // for (j = N - 1; j >= 0; j--) {
    //     while (i != 0 && X[j] - X[i - 1] <= 2 * R) {
    //         i--;
    //     }

    //     // log_range(i, j);
    //     if (rmin_prefix[X[i]] <= R - 2 && rmin_suffix[X[j]] <= R - 2) {
    //         return true;
    //     }
    // }

    return false;
}

map<i64, i64> find_req() {
    map<i64, i64> res;
    res[X[0]] = 0;

    i64 i = 0;
    for (i64 j = 1; j < N; j++) {
        while (i < j - 1) {
            i64 r1 = max(X[j] - X[i], res[X[i]] + 2);
            i64 r2 = max(X[j] - X[i + 1], res[X[i + 1]] + 2);

            if (r2 < r1) i++;
            else break;
        }

        res[X[j]] = max(X[j] - X[i], res[X[i]] + 2);
    }

    return res; 
}

#define TRANSFORM (1e9 + 7)

int main(void) {
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    cin >> N;
    X.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
        X[i] *= 2;
    }
    std::sort(X.begin(), X.end());

    rmin_prefix = find_req();

    std::reverse(X.begin(), X.end());
    for (int i = 0; i < N; i++) {
        X[i] = TRANSFORM - X[i];
    }
    map<i64, i64> rmin_suffix_tmp = find_req();
    for (auto p: rmin_suffix_tmp) {
        rmin_suffix[TRANSFORM - p.first] = p.second;
    }
    for (int i = 0; i < N; i++) {
        X[i] = TRANSFORM - X[i];
    }
    std::reverse(X.begin(), X.end());

    // printf("\nR -> L:\n");
    // for (i64 i = 0; i < N; i++) {
    //     printf("%lld: %lld\n", X[i], rmin_suffix[X[i]]);
    // } 

    i64 lo = 1;
    i64 hi = 1e10 + 1;

    // first true
    while (lo < hi) {
        i64 mid = (lo + hi) / 2;

        if (can_explode(mid)) {
            // everything after mid will be true
            // mid is also true though, but we can't
            // let hi land on something false
            hi = mid;
        } else {
            // let's try a new lo, this one didn't work
            lo = mid + 1;
        }
    }

    i64 ans = lo;
    if (ans % 2 == 0) {
        printf("%lld.0\n", ans / 2);
    } else {
        printf("%lld.5\n", ans / 2);
    }
}