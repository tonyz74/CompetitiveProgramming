#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

int main(void) {
    i64 n, x; cin >> n >> x;
    vector<pair<i64, int> > a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }

    // 8
    // 1 2 5 7

    std::sort(a.begin(), a.end());

    // for (pair<i64, i64> v: a) printf("%lld ", v.first);
    // printf("\n");

    for (int i = 0; i <= n - 3; i++) {
        int right = n - 1;

        for (int j = i + 1; j <= n - 2 && right > j; j++) {
            i64 now = a[i].first + a[j].first + a[right].first;
            // will need to increase j
            while (now > x && right > j) {
                right--;
                now = a[i].first + a[j].first + a[right].first;
            }

            if (now == x && right != j) {
                vector<int> sol { a[i].second, a[j].second, a[right].second };

                std::sort(sol.begin(), sol.end());
                for (int ans: sol) {
                    printf("%d ", ans + 1);
                }
                printf("\n");
                return 0;
            }
        }
    }

    printf("IMPOSSIBLE\n");
}