#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
using i64 = long long;

bool works[32000];

int main(void) {
    i64 N; cin >> N;
    vector<i64> a(N);

    i64 min_days = 8e9;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        min_days = min(min_days, a[i]);
    }

    i64 ans = 0;
    i64 max_L = (min_days / 4);
    for (i64 testL = max_L; testL >= 1; testL--) {
        set<i64> unique;
        printf("[%lld]:\t ", testL);
        for (i64 j = 0; j < N; j++) {
            unique.insert(a[j] % testL);
            // if (unique.size() > 3) {
            //     break;
            // }
            printf("%3lld(%lld) + %2lld     ", a[j] / testL, testL, a[j] % testL);
        } 

        if (unique.size() <= 3) {
            ans += testL;
            printf("  [Y]\n");
        } else {
            printf("  [N]\n");
        }
    }

    printf("%lld\n", ans);
}