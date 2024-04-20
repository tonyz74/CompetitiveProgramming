#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ctgmath>

using namespace std;
using i64 = long long;

int main(void) {
    map<i64, pair<i64, i64> > lut;
    map<i64, i64> log_table;
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

        vector<i64> S(35);
        vector<i64> T(35);

        map<i64, array<i64, 2> > rem;

        for (i64 i = 1; i <= N; i++) {
            // in - out = c
            i64 c = avg - A[i];

            // does not affect answer yet
            if (c == 0) continue;

            // 0 means negative, 1 means positive
            if (pows2.count(c) || pows2.count(-c)) {
                i64 place = log_table[abs(c)];
                rem[place][0 + (c > 0)]++;
            } else if (lut.count(c)) {
                S[lut[c].first] += 1;
                T[lut[c].second] += 1;
            } else {
                printf("No\n");
                return;
            }
        }

        // auto show = [&] () {
        //     for (i64 i = 0; i <= 30; i++) {
        //         printf("%d ", S[i]);
        //     }
        //     printf("\n");
        //     for (i64 i = 0; i <= 30; i++) {
        //         printf("%d ", T[i]);
        //     }
        //     printf("\n");
        // };
        // show();

        // highest bit
        for (auto p = rem.rbegin(); p != rem.rend(); p++) {
            i64 place = p->first;
            // printf("considering %d\n", place);

            // X in (goes to S)
            i64 X = p->second[1];
            // Y out (goes to T)
            i64 Y = p->second[0];

            // have to fix the disparity first
            i64 must_use = abs(S[place + 1] - T[place + 1]);
            if (S[place + 1] < T[place + 1]) {
                X -= must_use;
                S[place + 1] += must_use;
                T[place] += must_use;
            } else if (T[place + 1] < S[place + 1]) {
                Y -= must_use;
                T[place + 1] += must_use;
                S[place] += must_use;
            }

            if (X < 0 || Y < 0) {
                printf("No\n");
                return;
            }

            // printf("gave %d's S %d, T %d\n", place, X, Y);

            // remaining can just add to self
            S[place] += X;
            T[place] += Y;

            // show();
        }

        for (i64 i = 0; i <= 34; i++) {
            if (S[i] != T[i]) {
                // printf("at i = %d, %d %d\n", i, S[i], T[i]);
                printf("No\n");
                return;
            }
        }
        printf("Yes\n");
    };

    i64 T; cin >> T;
    while (T--) {
        work();
    }
}