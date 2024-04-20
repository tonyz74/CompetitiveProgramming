#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
using i64 = long long;

#define MAX_COLOR ((i64) ( 2 * 1e5 + 3))

i64 global_change = 0;
i64 indiv_change[MAX_COLOR];
vector<i64> A;
vector<i64> C;

vector<i64> pfx_by_color[MAX_COLOR];

int main(void) {
    std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

    i64 N; cin >> N;
    A.resize(N + 1);
    C.resize(N + 1);

    for (i64 i = 1; i <= N; i++) cin >> A[i];
    for (i64 i = 1; i <= N; i++) cin >> C[i];

    for (i64 i = 1; i <= N; i++) {
        if (pfx_by_color[C[i]].empty()) {
            pfx_by_color[C[i]].push_back(0);
        }
        pfx_by_color[C[i]].push_back(pfx_by_color[C[i]].back() + A[i]);
    }

    i64 Q; cin >> Q;
    for (i64 i = 1; i <= Q; i++) {
        i64 ty, col, arg;
        cin >> ty >> col >> arg;
        // printf("ty, col, arg: %d %d %d\n", ty, col, arg);

        if (ty == 1) {
            global_change += arg;
            indiv_change[col] -= arg;
        }

        if (ty == 2) {
            // adjust for by global change
            i64 local_change = indiv_change[col] + global_change;
            i64 lo = 0;
            // remember: we're 1 indexed (extra 0th elem), so we can try up to size - 1
            i64 hi = pfx_by_color[col].size() - 1;

            // find last true
            while (lo < hi) {
                i64 mid = (lo + hi + 1) / 2;
                // printf("mid: %lld, pfx: %lld, arg: %lld\n", mid, pfx_by_color[col][mid], arg);
                if (pfx_by_color[col][mid] + local_change * mid <= arg) {
                    lo = mid;
                } else {
                    hi = mid - 1;
                }
            }

            cout << lo << endl;
        }
    }
}