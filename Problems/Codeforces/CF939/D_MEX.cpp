#include <iostream>
#include <vector>
#include <bitset>
#include <functional>

using namespace std;
using i64 = long long;

vector<pair<i64, i64> > moves;

void do_moves(i64 L, i64 R) {
    i64 len = R - L + 1;
    if (len == 1) {
        return;
    } else if (len == 2) {
        moves.push_back(make_pair(L, R));
        moves.push_back(make_pair(L, L));
    } else {
        do_moves(L, R - 1);
        moves.push_back(make_pair(L, R));
        moves.push_back(make_pair(L, R - 1));
        do_moves(L, R - 1);
    }
}


int main(void) {
    i64 n; cin >> n;
    vector<i64> a(n + 1);
    for (i64 i = 1; i <= n; i++) cin >> a[i];

    auto sep = [&] (i64 mask) {
        // if they're on, we never touch them, and we set remaining ranges?
        vector<pair<i64, i64> > regions;

        i64 L = -1;
        for (i64 i = 1; i <= n; i++) {
            i64 is_on = (mask & (1ll << (i - 1ll)));

            if (is_on) {
                if (L != -1) {
                    regions.push_back(make_pair(L, i - 1));
                }
                L = -1;
            } else {
                if (L == -1) L = i;
            }
        }

        if (L != -1) regions.push_back(make_pair(L, n));

        return regions;
    };

    i64 best_ans = 0;
    i64 best_mask = 0;

    for (i64 mask = 0; mask < (1ll << n); mask++) {
        i64 ans = 0;
        // if they're on, we never touch them, and we set remaining ranges?
        vector<pair<i64, i64> > regions = sep(mask);
        for (i64 i = 1; i <= n; i++) {
            if (mask & (1ll << (i - 1ll))) {
                // printf("%lld, \n", a[i]);
                ans += a[i];
            }
        }

        for (auto p: regions) {
            i64 len = p.second - p.first + 1;
            ans += len * len;
        }

        if (ans > best_ans) {
            best_mask = mask;
            best_ans = ans;
        }
    }

    auto reg = sep(best_mask);
    // cout << bitset<18>(best_mask).to_string() << endl;

    for (auto p: reg) {
        int L = p.first, R = p.second;
        // printf("L %d, R %d\n", L, R);

        // make everything 0
        for (int i = L; i <= R; i++) {
            if (a[i] != 0) {
                moves.push_back(make_pair(i, i));
            }
        }

        do_moves(L, R);
        moves.push_back(make_pair(L, R));
    }

    printf("%lld %lld\n", best_ans, (i64) moves.size());
    for (auto mov: moves) {
        printf("%lld %lld\n", mov.first, mov.second);
    }
}