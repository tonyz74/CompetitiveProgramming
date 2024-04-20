#include <iostream>
#include <vector>
#include <map>

using namespace std;
using i64 = long long;

const i64 MOD = 998244353;

int main(void) {
    i64 pow2[5005];
    i64 x = 1;
    for (i64 i = 0; i <= 5003; i++) {
        pow2[i] = x;
        x *= 2;
        x %= MOD;
    }

    i64 n; cin >> n;
    vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    std::sort(a.begin() + 1, a.end());
    a.push_back(0);

    i64 ans = 0;
    for (i64 i = 1; i <= n; i++) {
        i64 eq = a[i];
        i64 num = 0;
        while (i <= n + 1 && a[i] == eq) {
            num++; i++;
        }

        // everything at i and later can be picked and get my value
        i64 n_cases_after = pow2[n - i + 1];
        i64 my_cases = pow2[num] - 1;

    }

    cout << ans << endl; 
}