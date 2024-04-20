#include <iostream>
#include <string>
#include <set>

using namespace std;

signed main(void) {
    int N; cin >> N;

    string S;
    cin >> S;

    int all_F = true;
    for (int i = 0; i < N; i++) {
        if (S[i] != 'F') {
            all_F = false;
            break;
        }
    }

    if (all_F) {
        printf("%d\n", N);
        for (int i = 0; i <= N - 1; i++) {
            printf("%d\n", i);
        }
        return 0;
    }

    // otherwise, it's some combination of BFFBs or BFFEs
    int base_excite = 0;
    int start = 0, end = 0;

    // is there a leading F-chunk?
    int start_type3 = 0;
    int end_type3 = 0;

    int i = 0;
    while (S[i] == 'F') {
        i++;
    }

    if (i != 0) {
        // printf("started with F chain of length %d\n", i);
        start_type3 = i;
    }

    int chnk_begin = 0;
    int F_cnt = 0;

    while (i < N) {
        // Skip over continuous B's and E's,
        // adding to total excitement along the way

        while (i + 1 < N && S[i + 1] != 'F') {
            if (S[i + 1] == S[i]) base_excite++;
            i++;
        }

        F_cnt = 0;
        chnk_begin = i;

        // I must've stopped before an F, or before the end
        if (i + 1 < N) i++;
        while (S[i] == 'F') {
            F_cnt++;
            i++;
        } 

        // printf("Block: %c [%d]F %c (%d, %d)\n", S[chnk_begin], F_cnt, S[i], chnk_begin, i);

        if (F_cnt != 0) {
            if (i != N) {
                int id = F_cnt;
                if (S[chnk_begin] != S[i]) {
                    id -= 1;
                }


                if (id % 2 == 0) {
                    // gonna be odd
                    start += 1;
                    end += (id + 1);
                } else {
                    // gonna be even
                    start += 0;
                    end += (id + 1);
                }
            } else {
                end_type3 = F_cnt;
            }
        }

        if (i >= N - 1) break;
    }

    // printf("base: %d, type3: %d, start: %d, end: %d\n", base_excite, type3_max, start, end);

    if (start_type3 >= 1 || end_type3 >= 1) {

        int actual_end = end + start_type3 + end_type3;
        int n_distinct = actual_end - start + 1;

        printf("%d\n", n_distinct);
        for (int i = start; i <= actual_end; i++) {
            printf("%d\n", base_excite + i);
        }

    } else {

        set<int> distinct_vals;
        for (int i = start; i <= end; i += 2) {
            distinct_vals.insert(base_excite + i);
        }

        printf("%lu\n", distinct_vals.size());
        for (int x: distinct_vals) {
            printf("%d\n", x);
        }

    }
}