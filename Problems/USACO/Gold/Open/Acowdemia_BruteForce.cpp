#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N, K, L; cin >> N >> K >> L;
    vector<i64> original_c(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> original_c[i];
    }
    std::sort(original_c.begin() + 1, original_c.end());
    std::reverse(original_c.begin() + 1, original_c.end());

    i64 lo = 0;
    i64 hi = N;

    auto check = [&] (i64 h) {
        if (h == 0) return true;

        multiset<i64> c;
        for (i64 i = 1; i <= h; i++) c.insert(original_c[i]);

        for (i64 i = 1; i <= K; i++) {
            vector<i64> add_back;
            for (i64 j = 1; j <= L && (i64) c.size() >= 1; j++) {
                i64 front = *c.begin();
                c.erase(c.find(front));
                add_back.push_back(front + 1);
            }

            for (i64 f: add_back) {
                c.insert(f);
            }
        }

        for (i64 v: c) {
            if (v < h) return false;
        }

        return true;
    };

    while (lo < hi) {
        i64 mid = (lo + hi + 1) / 2;

        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << endl;
}