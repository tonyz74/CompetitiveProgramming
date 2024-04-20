#include "atcoder/all"
#include <iostream>

using namespace std;

#define MAX_N ((int) (5 * 1e5 + 4))
#define MAX_VAL ((int) (5 * 1e5 + 4))

int op(int a, int b) {
    return max(a, b);
}

int e() {
    return 0;
}

// dp[i] => max len of subsq, if starting at i
int dp[MAX_N];
int a[MAX_N];

int main(void) {
    int N, D; cin >> N >> D;
    atcoder::segtree<int, op, e> st(MAX_VAL);

    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    int ans = 0;
    dp[N - 1] = 1;
    for (int i = N - 1; i >= 0; i--) {
        int lb = max(a[i] - D, 0);
        int ub = min(a[i] + D, MAX_VAL - 1);
        int mx = st.prod(lb, ub + 1);
        dp[i] = mx + 1;
        st.set(a[i], dp[i]);
        ans = max(ans, dp[i]);
    }

    printf("%d\n", ans);
}