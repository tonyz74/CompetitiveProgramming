#include <iostream>
#include <vector>
#include <set>
#include <ctgmath>
#include <cassert>

using namespace std;
using i64 = long long;

#define MAX_N ((int) 1e4 + 2)
i64 N;
i64 A[MAX_N];

bool check_L(i64 L) {
    set<i64> values;
    for (i64 i = 1; i <= N; i++) {
        values.insert(A[i] % L);

        if (values.size() > 3) break;
    }

    return values.size() <= 3;
}

int main(void) {
    cin >> N;
    set<i64> unique;
    for (i64 i = 1; i <= N; i++) {
        cin >> A[i];
        unique.insert(A[i]);
    }
    i64 max_L = *unique.begin() / 4;

    if (unique.size() <= 3) {
        printf("%lld\n", (max_L * (max_L + 1)) / 2);
        return 0;
    }

    vector<i64> first_four(5);
    auto it = unique.begin();
    for (i64 i = 1; i <= 4; i++) {
        first_four[i] = *it;
        it++;
    }

    vector<i64> tests;
    for (i64 i = 1; i <= 4; i++) {
        for (i64 j = i + 1; j <= 4; j++) {
            tests.push_back(abs(first_four[i] - first_four[j]));
        }
    }
    assert(tests.size() == 6);

    set<i64> possible_L;
    for (i64 X: tests) {
        // prime factorize X
        for (i64 x = 1; x * x <= X; x++) {
            if (X % x != 0) continue;

            possible_L.insert(X / x);
            possible_L.insert(x);
        }
    }

    i64 tot = 0;
    for (i64 L: possible_L) {
        if (L > max_L) continue;
        if (check_L(L)) tot += L;
    }
    printf("%lld\n", tot);
}