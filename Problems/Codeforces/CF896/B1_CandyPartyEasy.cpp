#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using i64 = long long;

int main(void) {
    map<i64, pair<i64, i64> > lut;
    for (i64 x = 0; x < 30; x++) {
        for (i64 y = 0; y < 30; y++) {
            lut[(1ll << x) - (1ll << y)] = make_pair((1 << x), (1 << y));
        }
    }

    i64 T; cin >> T;
    while (T--) {
        i64 N; cin >> N;
        vector<i64> A(N + 1);

        map<i64, int> give;

        i64 avg = 0;
        for (i64 i = 1; i <= N; i++) {
            cin >> A[i];
            avg += A[i];
        }

        if (avg % N != 0) {
            printf("No\n");
            goto done;
        }
        avg /= N;

        std::sort(A.begin() + 1, A.end());
        std::reverse(A.begin() + 1, A.end());

        for (i64 i = 1; i <= N; i++) {
            // in - out = c
            i64 c = avg - A[i];
            if (c == 0) continue;

            if (lut.count(c) == 0) {
                printf("No\n");
                goto done;
            }

            give[lut[c].first]++;   // will give this to somebody
            give[lut[c].second]--;  // will take somebody's this
        }
        
        for (auto p: give) {
            if (p.second != 0) {
                printf("No\n");
                goto done;
            }
        }
        printf("Yes\n");

        done: (void) 0;
    }
}