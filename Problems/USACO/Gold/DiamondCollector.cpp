#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

int main(void) {
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);

    i64 N; cin >> N;
    i64 K; cin >> K;

    vector<i64> diamonds(N);
    for (i64 i = 0; i < N; i++) {
        cin >> diamonds[i];
    }

    std::sort(diamonds.begin(), diamonds.end());
    // for (i64 d: diamonds) printf("%lld ", d);
    // printf("\n");

    vector<i64> sfx_max(N);
    i64 i = N - 1;
    for (i64 j = N - 1; j >= 0; j--) {
        if (j < i) i = j;

        if (i != N - 1) {
            sfx_max[i] = max(sfx_max[i], sfx_max[i + 1]);
        }

        // slide i left until we can't anymore
        while (i > 0 && diamonds[j] - diamonds[i - 1] <= K) {
            i--;
            sfx_max[i] = max(sfx_max[i], sfx_max[i + 1]);
            sfx_max[i] = max(sfx_max[i], j - i + 1);
        }
    }

    i64 ans = 0;

    i64 j = 0;
    for (i64 i = 0; i < N; i++) {
        if (j < i) j = i;

        while (j < N - 1 && diamonds[j + 1] - diamonds[i] <= K) {
            j++;
        }

        i64 otherside = 0;
        if (j < N - 1) otherside = sfx_max[j + 1];

        ans = max(ans, otherside + (j - i + 1));
    }

    cout << ans << endl;
}