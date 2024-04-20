#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;
using i64 = long long;

#define NEG_INF ((i64) -1e11)

vector<string> rev = {
    "",
    "A", "B", "C",
    "A + B", "A + C", "B + C",
    "A + B + C",
    ""
};

enum type {
    tA = 1, tB, tC,
    tA_B, tA_C, tB_C,
    tA_B_C
};

void get_single_values_from(i64 from, i64 p, i64 q, vector<i64>& res) {
    if (res[p] > NEG_INF) {
        res[q] = from - res[p];
        if (res[q] >= 1e9) {
            printf("%lld %lld %s %s\n", from, res[p], rev[p].c_str(), rev[q].c_str());
            exit(-1);
        }
    }

    if (res[q] > NEG_INF) {
        res[p] = from - res[q];
    }
}

void solve() {
    int N; cin >> N;
    // int total_cases = 0;

    vector<i64> X(N + 1);
    for (int i = 0; i < N; i++) cin >> X[i];

    vector<type> cfg = { tA, tB, tC, tA_B, tA_C, tB_C, tA_B_C };

    int sols = 0;
    set<pair<i64, pair<i64, i64> > > presence;

    do {
        i64 vA, vB, vC;
        vector<i64> res(11, NEG_INF);

        for (int i = 0; i < N; i++) {
            res[cfg[i]] = X[i];
        }

        // printf("testing sequence: ");
        // for (int i = 0; i < N; i++) {
        //     printf("%s ", rev[cfg[i]].c_str());
        // }
        // cout << endl;

        // only A + B + C and pairwise sums within, this is guaranteed (len = 4 at least)
        if (res[tA] <= NEG_INF && res[tB] <= NEG_INF && res[tC] <= NEG_INF) {
            i64 all = res[tA_B_C];
            res[tC] = all - res[tA_B];
            res[tB] = all - res[tA_C];
            res[tA] = all - res[tB_C];
        } else {
            while (res[tA] <= NEG_INF || res[tB] <= NEG_INF || res[tC] <= NEG_INF) { 
                // printf("%lld %lld %lld\n", res[tA], res[tB], res[tC]);
                if (res[tA] > NEG_INF && res[tB] > NEG_INF) res[tA_B] = res[tA] + res[tB];
                if (res[tA] > NEG_INF && res[tC] > NEG_INF) res[tA_C] = res[tA] + res[tC];
                if (res[tB] > NEG_INF && res[tC] > NEG_INF) res[tB_C] = res[tB] + res[tC];

                for (int i = 0; i < N; i++) {
                    if (cfg[i] == tA_B_C) {
                        get_single_values_from(X[i], tA_B, tC, res);
                        get_single_values_from(X[i], tA_C, tB, res);
                        get_single_values_from(X[i], tB_C, tA, res);
                    }

                    if (cfg[i] == tA_B) get_single_values_from(X[i], tA, tB, res);
                    if (cfg[i] == tB_C) {
                        get_single_values_from(X[i], tB, tC, res);
                    }
                    if (cfg[i] == tA_C) get_single_values_from(X[i], tA, tC, res);

                    if ((res[tA] != NEG_INF && res[tA] <= 0) || (res[tB] != NEG_INF && res[tB] <= 0)
                        || (res[tC] != NEG_INF && res[tC] <= 0)) {
                        goto skip;
                    }
                }
            }
        }

        vA = res[tA];
        vB = res[tB];
        vC = res[tC];
        if (vA > 0 && vB > 0 && vC > 0 && vA <= vB && vB <= vC) {
            bool fail = false;
            set<i64> final_check = { vA, vB, vC, vA + vB, vA + vC, vB + vC, vA + vB + vC };
            for (int j = 0; j < N; j++) {
                if (!final_check.count(X[j])) {
                    fail = true;
                    break;
                }
            }

            auto repr = make_pair(vA, make_pair(vB, vC));
            if (!presence.count(repr) && !fail) {
                presence.insert(repr);
                sols++;
            }
        }

        skip: (void) 0;

        std::reverse(cfg.begin() + N, cfg.end());
    } while (next_permutation(cfg.begin(), cfg.end()));

    cout << sols << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}