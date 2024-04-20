#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

i64 N, M;
vector<i64> X;

i64 get_cw_dist(i64 a, i64 b) {
    return b - a;
}

i64 get_ccw_dist(i64 a, i64 b) {
    if (b < a) std::swap(a, b);
    return (N - get_cw_dist(a, b)) % N;
}

int main(void) {
    cin >> N >> M;
    X.resize(M + 1);
    for (i64 i = 1; i <= M; i++) cin >> X[i];
    // pfx[i], i means cutting the edge starting at i
    vector<i64> pfx(N + 10);
    i64 initial_dist = 0;

    for (i64 i = 1; i <= M - 1; i++) {
        i64 a = X[i], b = X[i + 1];
        if (b < a) std::swap(a, b);

        i64 cw_dist = b - a;
        i64 ccw_dist = (N - (cw_dist)) % N;
        initial_dist += cw_dist;

        // printf("\n");
        // printf("for %lld and %lld, cw is %lld and ccw is %lld\n", a, b, cw_dist, ccw_dist);
        // printf("adding %lld to pfx[a], adding %lld to pfx[b]\n", cw_dist - ccw_dist, ccw_dist - cw_dist);
        // we need to get from a to b
        pfx[a] += (ccw_dist - cw_dist);
        pfx[b] += (cw_dist - ccw_dist);
    }

    // printf("originally took %lld\n", initial_dist);
    // for (i64 i = 1; i <= N; i++) {
    //     printf("%lld ", pfx[i]);
    // }
    // printf("\n\n");

    i64 marker = initial_dist;
    i64 ans = initial_dist;

    for (i64 i = 1; i <= N; i++) {
        marker += pfx[i];
        ans = min(ans, marker);
    }

    cout << ans << endl;
}