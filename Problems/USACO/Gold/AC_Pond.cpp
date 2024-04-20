#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;

#define MAX_N 805

int MED = 0;
int MED_FROM_BOTTOM = 0;

int N, K;
int grid[MAX_N][MAX_N];
int ps[MAX_N][MAX_N];

int get_ksize_sum(int i, int j) {
    int end_i = i + K - 1;
    int end_j = j + K - 1;
    assert(end_i <= N && end_j <= N);

    return ps[end_i][end_j] - ps[i - 1][end_j] - ps[end_i][j - 1] + ps[i - 1][j - 1];
}

bool median_lteq(int val) {
    memset(ps, 0, sizeof(ps));

    // calculate 2d prefix sums on ineq
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int ineq = grid[i][j] > val;
            ps[i][j] = ineq + ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1];
        }
    }

    for (int i = 1; i <= N - K + 1; i++) {
        for (int j = 1; j <= N - K + 1; j++) {
            int ks = get_ksize_sum(i, j);
            int num_zeroes = K * K - ks;
            if (num_zeroes >= MED_FROM_BOTTOM) return true;
        }
    }

    return false;
}

int main(void) {
    cin >> N >> K;
    MED = K * K / 2 + 1;
    MED_FROM_BOTTOM = K * K - MED + 1;

    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
        cin >> grid[i][j];
    }

    // find first true
    int lo = 0;
    int hi = 1e9 + 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (median_lteq(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d\n", lo);
}