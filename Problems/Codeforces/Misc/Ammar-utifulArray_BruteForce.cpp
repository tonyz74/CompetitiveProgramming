#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;
using i64 = long long;

vector<i64> A;
vector<i64> C;

map<i64, vector<i64> > by_color;

int main(void) {
    i64 N; cin >> N;
    A.resize(N + 1);
    C.resize(N + 1);

    set<i64> colors;
    for (i64 i = 1; i <= N; i++) cin >> A[i];
    for (i64 i = 1; i <= N; i++) {
        cin >> C[i];
        colors.insert(C[i]);
    }

    for (i64 c: colors) by_color[c].push_back(0);
    for (i64 i = 1; i <= N; i++) by_color[C[i]].push_back(A[i]);

    i64 Q; cin >> Q;
    for (i64 i = 1; i <= Q; i++) {
        i64 ty, col, arg; cin >> ty >> col >> arg;

        if (ty == 1) {
            for (i64 color: colors) {
                if (color != col) {
                    for (i64 j = 1; j < (i64) by_color[color].size(); j++) {
                        by_color[color][j] += arg;
                    }
                }
            }
        }

        if (ty == 2) {
            i64 total = 0;
            i64 n_elems = by_color[col].size() - 1;

            // for (i64 k = 1; k <= n_elems; k++) {
            //     printf("%lld ", by_color[col][k]);
            // }
            // printf("\n");

            i64 j = 0;
            for (i64 k = 1; k <= n_elems; k++) {
                if (total + by_color[col][k] <= arg) {
                    total += by_color[col][k];
                    j++;
                } else {
                    break;
                }
            }

            printf("%lld\n", j);
        }
    }
}