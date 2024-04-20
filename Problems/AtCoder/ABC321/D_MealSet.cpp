#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

int main(void) {
    ll N, M, P;
    cin >> N >> M >> P;

    vector<ll> A(N, 0);
    vector<ll> B(M, 0);

    for (ll i = 0; i < N; i++) cin >> A[i];
    for (ll i = 0; i < M; i++) cin >> B[i];

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    vector<ll> prefix_sum(M + 1, 0);
    for (ll i = 1; i <= M; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + B[i - 1];
    }
    
    // printf("%d\n\n", P);

    // for (int i = 0; i < A.size(); i++) {
    //     printf("%d ", A[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < prefix_sum.size(); i++) {
        // printf("%d ", prefix_sum[i]);
    // }
    // printf("\n");

    ll total = 0;

    // 3 5
    // 1 6

    // sort and binary search to find cutoff point
    for (ll i = 0; i < N; i++) {
        ll elem = A[i];
        ll bound = P - elem;

        // find first element greater than or equal to bound (replace all
        // stuff afterwards with P).
        auto it = lower_bound(B.begin(), B.end(), bound);
        ll pos = it - B.begin();

        // printf("pos = %llu for i = %llu (A[i] = %llu), *it = %llu\n", pos, i, A[i], *it);
        total += prefix_sum[pos] + pos * elem;
        total += (B.size() - pos) * P;
    }

    printf("%llu\n", total);
}