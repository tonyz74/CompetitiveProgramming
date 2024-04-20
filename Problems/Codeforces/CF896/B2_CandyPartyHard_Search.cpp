#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ctgmath>

using namespace std;
using i64 = long long;

int main(void) {
    map<i64, i64> log_table;
    map<i64, pair<i64, i64> > lut;
    for (i64 x = 0; x < 33; x++) {
        log_table[(1ll << x)] = x;
        for (i64 y = 0; y < 33; y++) {
            lut[(1ll << x) - (1ll << y)] = make_pair(x, y);
        }
    }
    set<i64> pows2;
    for (i64 i = 0; i <= 33; i++) {
        pows2.insert((1ll << i));
    }

    auto work = [&] () {
        i64 N; cin >> N;
        vector<i64> A(N + 1);

        i64 avg = 0;
        for (i64 i = 1; i <= N; i++) {
            cin >> A[i];
            avg += A[i];
        }
        avg /= N;

        vector<int> S(34, 0);
        vector<int> T(34, 0);

        vector<i64> remaining(1);
        for (int i = 1; i <= N; i++) {
            i64 c = avg - A[i];
            if (c == 0) continue;

            if (pows2.count(abs(c))) {
                remaining.push_back(c);
            } else if (lut.count(c)) {
                S[lut[c].first] += 1;
                T[lut[c].second] += 1;
            } else {
                printf("No\n");
                return;
            }
        }

        int done = false;

        auto show = [&] () {
            // for (int i = 0; i <= 6; i++) {
            //     printf("%d ", S[i]);
            // }
            // printf("\n");
            // for (int i = 0; i <= 6; i++) {
            //     printf("%d ", T[i]);
            // }
            // printf("\n");
        };

        function<void(int)> dfs = [&] (int i) {
            if (done) return;
            if (i == (int) remaining.size()) {
                // printf("found something\n");

                // compare
                int all = true;
                for (i64 j = 0; j < 34; j++) {
                    if (S[j] != T[j]) {
                        all = false;
                        break;
                    }
                }

                if (all) {
                    done = true;
                    show();
                }
                return;
            }

            // two choices:
            int place = log_table[abs(remaining[i])];

            if (remaining[i] < 0) {
                S[place]++;
                T[place + 1]++;
                dfs(i + 1);
                S[place]--;
                T[place + 1]--;

                T[place]++;
                dfs(i + 1);
                T[place]--;
            } else {
                T[place]++;
                S[place + 1]++;
                dfs(i + 1);
                T[place]--;
                S[place + 1]--;

                S[place]++;
                dfs(i + 1);
                S[place]--;
            }
        };

        dfs(1);

        if (done) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    };

    i64 T; cin >> T;
    while (T--) {
        work();
    }
}