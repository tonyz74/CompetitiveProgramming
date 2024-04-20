#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N, M; cin >> N >> M;

    auto solve_slow = [&] () {
        set<i64> spare;
        for (int i = 1; i <= N; i++) {
            spare.insert(i);
        }

        i64 rem_need = M;
        for (i64 i = 1; i <= N; i++) {
            i64 N_left = N - i + 1;
            i64 pos = 1;
            i64 val = -1;

            for (auto it = spare.begin(); it != spare.end(); it++) {
                val = *it;

                i64 rem = N_left - 1;
                i64 before = pos - 1;

                // printf("if i picked %d (pos = %d): before %d, all dec %d\n", val, pos, before, (rem * (rem - 1)) / 2);
                if (before + (rem * (rem - 1)) / 2 >= rem_need) {
                    // pick this one
                    break;
                }

                pos++;
            }

            assert(pos != N_left + 1);

            rem_need -= (pos - 1);
            spare.erase(val);

            printf("%lld ", val);
        }
        printf("\n");
    };
    (void) solve_slow;

    auto solve_fast = [&] () {
        vector<i64> spare(N + 1);
        for (i64 i = 1; i <= N; i++) {
            spare[i] = i;
        }

        i64 rem_need = M;
        for (i64 i = 1; i <= N; i++) {
            i64 N_left = N - i + 1;
            i64 rem = N_left - 1;

            i64 pos = max(rem_need - (rem * (rem - 1)) / 2 + 1, 1ll);
            // for (i64 x: spare) {
            //     printf("%lld ", x);
            // }
            // printf(" and pos: %lld\n", pos);

            assert(pos <= N_left);

            rem_need -= pos - 1;

            printf("%lld ", spare[pos]);
            spare.erase(spare.begin() + pos);
        }
        printf("\n");
    };

    solve_fast();
}