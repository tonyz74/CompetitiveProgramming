#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int N; cin >> N;
    vector<long long> b(N + 1);

    for (int i = 1; i <= N; i++) cin >> b[i];

    vector<long long> pre(N + 1);
    vector<long long> post(N + 1);

    for (int i = 1; i <= N; i++) {
        pre[i] = max(pre[i - 1], b[i] + i);
        // printf("%lld ", pre[i]);
    }
    // printf("\n");

    for (int i = N; i >= 1; i--) {
        if (i == N) {
            post[i] = b[i] - N;
        } else {
            post[i] = max(post[i + 1], b[i] - i);
        }
        // printf("%lld ", post[i]);
    }
    // printf("\n");

    long long ans = 0;
    for (int mid_idx = 2; mid_idx <= N - 1; mid_idx++) {
        long long best_pre = pre[mid_idx - 1];
        long long best_post = post[mid_idx + 1];

        ans = max(b[mid_idx] + best_pre + best_post, ans);
    }

    cout << ans << endl;
}

int main(void) {
    int t; cin >> t;

    for (int i = 0; i < t; i++) solve();
}