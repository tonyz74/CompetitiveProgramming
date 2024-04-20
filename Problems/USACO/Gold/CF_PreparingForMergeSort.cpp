#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using i64 = long long;

template<typename F>
i64 first_true(i64 lo, i64 hi, F func) {
    while (lo < hi) {
        i64 mid = (lo + hi) / 2;

        if (func(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return lo;
}

int main(void) {
    int n; cin >> n;
    vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // [i.back() for i in parts] is a non-increasing sequence.
    // if there was a larger back, it'd be put at the end of
    // another subsequence earlier on. Thus it's sorted.
    vector<vector<i64> > parts;

    // printf("running on test arr\n");
    // vector<bool> test_arr = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 };
    // auto is_equal = [&test_arr] (i64 mid) { return test_arr[mid] == true; };
    // printf("%lld\n", first_true(0, 9, is_equal));

    // return 0;

    for (int i = 0; i < n; i++) {
        int j = 0;
        bool found = false;

        // printf("\ni: %d\n", i);
        // for (auto v: parts) {
        //     printf("%lld ", v.back());
        // }
        // printf("\n");

        auto pred = [&parts, &a, i] (i64 mid) {
            return parts[mid].back() < a[i];
        };

        if (parts.size() == 0 || parts.back().back() >= a[i]) {
            found = false;
            j = parts.size();
        } else {
            found = true;
            j = first_true(0, (parts.size() - 1), pred);
            // printf("found, setting j to %d\n", j);
        }

        // for (; j < (int) parts.size(); j++) {
        //     if (parts[j].back() < a[i]) {
        //         found = true;
        //         break;
        //     }
        // } 
        // printf("found j to be %d (found = %d)\n", j, (int) found);

        if (!found) {
            parts.push_back(vector<i64>(1, a[i]));
        } else {
            parts[j].push_back(a[i]);
        }
    }

    for (int i = 0; i < (int) parts.size(); i++) {
        for (i64 x: parts[i]) {
            printf("%lld ", x);
        }
        printf("\n");
    }
}