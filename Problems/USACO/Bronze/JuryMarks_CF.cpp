#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

using i64 = long long;

set<i64> total_vals;

int main(void) {
    int k, n; cin >> k >> n;

    vector<i64> a(k + 1);
    for (i64 i = 1; i <= k; i++) cin >> a[i];

    vector<i64> b(n + 1);
    for (i64 i = 1; i <= n; i++) cin >> b[i];

    // a is in fixed order
    // their relative sizes must follow a
    vector<i64> presum(k + 1, 0);
    for (int i = 1; i <= k; i++) {
        presum[i] = presum[i - 1] + a[i];
    } 


    // key: how much off from original value
    // value: index of appropriate placement
    map<i64, i64> displacement;

    // sort this, so we know which order to add in
    vector<pair<i64, i64> > ordering(1);
    for (int i = 1; i <= k; i++) {
        ordering.push_back(make_pair(presum[i], i));
        displacement[presum[i]] = i;
    }
    sort(ordering.begin() + 1, ordering.end());

    // though b isn't in chronological order, we need to
    // assign it in value size order
    sort(b.begin() + 1, b.end());

    // enumerate where b starts
    for (i64 i = 1; i <= k; i++) {
        // try to put b[1] here at position k

        // printf("placing b[1] at %d (disp = %d)\n", ordering[i].second, ordering[i].first);

        int fail = false;
        for (int j = 2; j <= n; j++) {
            i64 disp = ordering[i].first + (b[j] - b[1]);
            // printf("b[j]: %d, disp = %d\n", b[j], disp);
            i64 idx = displacement[disp];
            if (idx == 0) {
                fail = true;
                break;
            }
        }

        if (!fail) {
            total_vals.insert(b[1] - ordering[i].first);
        }
    }

    // for (int x: total_vals) {
    //     printf("%d\n", x);
    // }
    cout << total_vals.size() << endl;
}