#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using i64 = long long;

void solve() {
    i64 N, K; cin >> N >> K;

    i64 best = 0;
    vector<i64> A(N + 1);
    vector<i64> B(N + 1);

    {
        vector<pair<i64, i64> > bob_alice(N + 1);
        for (i64 i = 1; i <= N; i++) {
            cin >> bob_alice[i].second;
        }
        for (i64 i = 1; i <= N; i++) {
            cin >> bob_alice[i].first;
        }

        std::sort(bob_alice.begin() + 1, bob_alice.end());
        std::reverse(bob_alice.begin() + 1, bob_alice.end());

        for (i64 i = 1; i <= N; i++) {
            B[i] = bob_alice[i].first;
            A[i] = bob_alice[i].second;
        }
    }

    // for (i64 i = 1; i <= N; i++) {
    //     printf("%lld ", A[i]);
    // }
    // cout << endl;
    // for (i64 i = 1; i <= N; i++) {
    //     cout << B[i] << " ";
    // }
    // cout << endl;

    vector<i64> profit_after(N + 2);
    for (i64 i = N; i >= 1; i--) {
        profit_after[i] = profit_after[i + 1];
        if (B[i] > A[i]) {
            profit_after[i] += B[i] - A[i];
        }
    }

    i64 min_sum = 0;
    multiset<i64> ms;

    for (i64 i = 1; i <= K - 1; i++) {
        ms.insert(A[i]);
        min_sum += A[i];
    }

    for (i64 br = K; br <= N; br++) {
        min_sum += A[br];
        ms.insert(A[br]);

        if ((i64) ms.size() > K) {
            i64 worst = *ms.rbegin();
            min_sum -= worst;
            ms.erase(ms.find(worst));
        }

        i64 this_ans = profit_after[br + 1] - min_sum;
        best = max(best, this_ans);
    }

    cout << best << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}
