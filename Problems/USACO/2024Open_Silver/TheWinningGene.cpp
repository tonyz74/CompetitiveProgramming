#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <algorithm>

using namespace std;
using u64 = unsigned long long;

u64 pow_base[3001];
const u64 base = 233ull;
const u64 MAX_N = 3001;

u64 N;
string DNA;
vector<u64> pfx;

// first starts at i, second starts at j
u64 max_equal_len[MAX_N][MAX_N];

// for the substring starting at i, what's its
// ordering when in length L substrings?
// ordering[L][i]
u64 ordering[MAX_N][MAX_N];

// for the substring starting at i under length L,
// what is my distance from the first one smaller than me?
vector<vector<u64> > dist_lt_LHS;
vector<vector<u64> > dist_lt_RHS;

void precompute_pow() {
    u64 pow = 1;
    for (u64 i = 0; i <= 3000ull; i++) {
        pow_base[i] = pow;
        pow *= base;
    }
}

bool is_equal(u64 L1, u64 R1, u64 L2, u64 R2) {
    // if lengths are not equal obviously no
    if ((R1 - L1 + 1) != (R2 - L2 + 1)) return false;

    u64 dist_to_end_1 = N - L1;
    u64 dist_to_end_2 = N - L2;

    u64 hash1 = pow_base[dist_to_end_1] * (pfx[R1] - pfx[L1 - 1]);
    u64 hash2 = pow_base[dist_to_end_2] * (pfx[R2] - pfx[L2 - 1]);

    return hash1 == hash2;
}

int main(void) {
    cin >> N; cin >> DNA;
    DNA = "$" + DNA;
    pfx.resize(N + 1, 0);

    dist_lt_LHS.resize(N + 1, vector<u64>(N + 1));
    dist_lt_RHS.resize(N + 1, vector<u64>(N + 1));

    precompute_pow();

    for (u64 i = 1; i <= N; i++) {
        pfx[i] = pfx[i - 1] + (((u64) DNA[i]) * pow_base[i]);
        // printf("%llu\n", pfx[i]);
    }

    for (u64 i = 1; i <= N; i++) {
        for (u64 j = 1; j <= N; j++) {
            if (!is_equal(i, i, j, j)) {
                max_equal_len[i][j] = 0;
            } else {
                u64 lo = 1;
                u64 hi = min(N - i + 1, N - j + 1);

                // find last that is equal
                while (lo < hi) {
                    u64 mid = (lo + hi + 1) / 2;

                    if (is_equal(i, i + mid - 1, j, j + mid - 1)) { 
                        lo = mid;
                    } else {
                        hi = mid - 1;
                    }
                }

                max_equal_len[i][j] = lo;
            }
        }
    }

    // for (u64 i = 1; i <= N; i++) {
    //     for (u64 j = 1; j <= N; j++) {
    //         printf("%4llu  ", max_equal_len[i][j]);
    //     }
    //     printf("\n");
    // }

    for (u64 L = 1; L <= N; L++) {
        vector<u64> to_sort(1);
        for (u64 i = 1; i <= N - (L - 1); i++) {
            to_sort.push_back(i);
        }

        std::sort(to_sort.begin() + 1, to_sort.end(), [&] (u64 a, u64 b) {
            // put the smaller one first
            if (max_equal_len[a][b] >= L) {
                return a < b;
            }

            u64 first_diff = max_equal_len[a][b] + 1;
            if (DNA[a + first_diff - 1] < DNA[b + first_diff - 1]) {
                // a is less than b
                return true;
            } else {
                // a is not less than b
                return false;
            }
        });

        for (u64 i = 1; i <= N - (L - 1); i++) {
            ordering[L][to_sort[i]] = i;
        }
        for (u64 i = N - (L - 1) + 1; i <= N; i++) {
            ordering[L][i] = 1e4;
        }
    }

    // printf("\n\n\n");
    // for (u64 L = 1; L <= N; L++) {
    //     for (u64 i = 1; i <= N; i++) {
    //         printf("%5llu  ", ordering[L][i]);
    //     }
    //     printf("\n");
    // }

    vector<u64> ans(N + 1, 0);

    for (u64 L = 1; L <= N; L++) {
        stack<u64> mono_lhs;
        stack<u64> mono_rhs;

        for (u64 i = 1; i <= N - (L - 1); i++) {
            // stores indices
            while (!mono_lhs.empty() && ordering[L][mono_lhs.top()] > ordering[L][i]) {
                mono_lhs.pop();
            }

            if (mono_lhs.empty()) {
                dist_lt_LHS[L][i] = i;
            } else {
                dist_lt_LHS[L][i] = (i - mono_lhs.top());
            }

            mono_lhs.push(i);
        }

        for (u64 i = N - (L - 1); i >= 1; i--) {
            while (!mono_rhs.empty() && ordering[L][mono_rhs.top()] > ordering[L][i]) {
                mono_rhs.pop();
            }

            if (mono_rhs.empty()) {
                dist_lt_RHS[L][i] = N - i + 1;
            } else {
                dist_lt_RHS[L][i] = (mono_rhs.top() - i);
            }

            mono_rhs.push(i);
        }

        vector<int> diff_array(N + 2);

        for (u64 i = 1; i <= N - (L - 1); i++) {
            u64 left_border = i - (dist_lt_LHS[L][i] - 1);
            u64 right_border = i + (dist_lt_RHS[L][i] - 1);
            right_border += L - 1;
            right_border = min(right_border, N);

            u64 max_K = (right_border - left_border + 1);

            // printf("of %lld: left %lld, right %lld\n", i, left_border, right_border);

            if (max_K >= L) {
                diff_array[L]++;
                diff_array[max_K + 1]--;
            }
        }

        // can find the number included for each K
        // add this to total

        int cnt = 0;
        for (u64 K = L; K <= N; K++) {
            cnt += diff_array[K];
            // number included for K is cnt
            // -> cnt has 1 more (this K)
            ans[cnt]++;
        }
    }

    // printf("\n\n\n");
    // for (u64 L = 1; L <= N; L++) {
    //     for (u64 i = 1; i <= N; i++) {
    //         printf("%3llu  ", dist_lt_LHS[L][i]);
    //     }
    //     printf("\n");
    // }

    // printf("\n\n\n");
    // for (u64 L = 1; L <= N; L++) {
    //     for (u64 i = 1; i <= N; i++) {
    //         printf("%3llu  ", dist_lt_RHS[L][i]);
    //     }
    //     printf("\n");
    // }

    for (u64 v = 1; v <= N; v++) {
        printf("%lld\n", ans[v]);
    }
}