#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define MAX_N ((int) (3 * 1e5 + 4))
#define MAX_M (8 + 1)

int N, M;
int A[MAX_N][MAX_M];

bool check_ans(int x, int show) {
    // all M bits set
    int ALL = (1 << M) - 1;

    map<int, int> masks;
    for (int i = 1; i <= N; i++) {
        int mask = 0;
        for (int j = 1; j <= M; j++) {
            if (A[i][j] >= x) {
                mask |= (1 << (j - 1));
            }
        }

        masks[mask] = i;
    }

    for (auto mask1: masks) {
        for (auto mask2: masks) {
            if ((mask1.first | mask2.first) == (ALL)) {
                if (show) {
                    printf("%d %d\n", mask1.second, mask2.second);
                }
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> A[i][j];
        }
    }

    int lo = 0;
    int hi = 1e9;

    // find last true 
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check_ans(mid, 0)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    int ans = lo;
    check_ans(ans, 1);
}