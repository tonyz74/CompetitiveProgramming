#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

using i64 = int;

i64 n, k;
vector<i64> a;

bool valid(int mid) {
    vector<i64> alt;
    for (i64 i = 0; i < n; i++) {
        if (a[i] < mid) alt.push_back(-1);
        else alt.push_back(1);
    }
    
    // cout << "mid " << mid << endl;
    // for (int x: alt) {
    //     cout << x << " ";
    // }
    // cout << endl;

    vector<i64> pfx(n);
    vector<i64> pmin(n);

    pfx[0] = alt[0];
    pmin[0] = min(0, alt[0]);

    for (int i = 1; i < n; i++) {
        pfx[i] = pfx[i - 1] + alt[i];
        pmin[i] = min(pmin[i - 1], pfx[i]);
    }

    // for (int p: pfx) {
    //     printf("%d ", p);
    // }
    // cout << endl;

    i64 max_subarray_sum = 0;
    for (i64 i = k - 1; i < n; i++) {
        i64 sub = 0;
        if (i > k - 1) sub = pmin[i - k];
        max_subarray_sum = max(pfx[i] - sub, max_subarray_sum);
    }

    return max_subarray_sum > 0; 
}

i64 last_true(i64 lo, i64 hi) {
    while (lo < hi) {
        // round up
        i64 mid = (lo + hi + 1) / 2;

        if (valid(mid)) {
            // if mid works, all numbers less than equal to mid works
            lo = mid;
        } else {
            // if mid doesn't work, we only care about mid - 1 to lo now
            hi = mid - 1;
        }
    }

    return lo;
}

int main(void) {
    cin >> n >> k;
    a.resize(n);
    set<i64> values;

    for (i64 i = 0; i < n; i++) {
        cin >> a[i];
        values.insert(a[i]);
    }

    i64 last = last_true(1, n + 1);
    // first value not greater than (lteq)
    cout << last << endl;
}