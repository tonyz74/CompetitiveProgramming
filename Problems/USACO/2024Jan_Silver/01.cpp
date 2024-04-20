#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
using i64 = long long;

struct ord {
    int a;
    int h;

    bool operator<(const ord& rhs) const {
        return make_pair(h, -a) < make_pair(rhs.h, rhs.a * -1);
    }
};

vector<i64> next_greatest_elem(const vector<i64>& v) {
    i64 N = v.size() - 1;
    vector<i64> output(v.size());
    for (i64 i = 1; i <= N; i++) {
        i64 pos = -1;
        for (i64 j = i; j <= N; j++) {
            if (v[j] > v[i]) {
                pos = j;
                break;
            }
        }

        output[i] = pos;
    }

    return output;
}

void solve() {
    i64 N, Q, C; cin >> N >> Q >> C;
    vector<i64> state(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> state[i];
    }

    vector<ord> ords(Q);
    for (i64 i = 0; i < Q; i++) {
        cin >> ords[i].a >> ords[i].h;
    }
    std::sort(ords.begin(), ords.end());

    // for (int i = 0; i < Q; i++) {
    //     printf("%d %d\n", ords[i].a, ords[i].h);
    // }

    set<i64> prev;

    i64 q = 0;
    for (i64 i = 1; i <= N; i++) {
        // handle validation and setting
        if (i == ords[q].h) {
            while (q != Q && i == ords[q].h) {
                i64 min_val = 1;
                if (prev.size() != 0) {
                    min_val = max(min_val, *prev.rbegin());
                }

                if (state[i] == 0) {
                    state[i] = min_val + 1;

                    if (state[i] > C) {
                        printf("-1\n");
                        return;
                    }
                }
                prev.insert(state[i]);
                q++;
            }
        } else {
            if (state[i] != 0) {
                prev.insert(state[i]);
            }
        }
    }


    for (i64 i = 1; i <= N; i++) {
        printf("%lld", state[i]);
        if (i != N) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void) {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}