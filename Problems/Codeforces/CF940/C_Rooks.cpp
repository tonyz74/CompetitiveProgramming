#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

const i64 MOD = 1e9 + 7;
const i64 MAX_N = 3 * 1e5 + 7;

i64 fastpow(i64 x, i64 power) {
    i64 ans = 1;

    // x^12 = x^4 * x^8
    // effectively splitting into powers of two

    while (power != 0) {
        if (power % 2 == 1) {
            ans = ans * x;
            power -= 1;
        }

        x = x * x;
        x %= MOD;
        ans %= MOD;
        power /= 2;
    }

    return ans;
}

// x^(mod - 2) => the modular inverse of x under base mod
i64 modular_inverse(i64 x) {
    // compute x^(base - 2) % base
    return fastpow(x, MOD - 2);
}

i64 fact[MAX_N];
i64 odd_fact[MAX_N];
i64 inv_fact[MAX_N];
i64 pow2_save[MAX_N];

void solve() {
    i64 n, k; cin >> n >> k;
    vector<bool> taken(n + 1);

    for (i64 op = 1; op <= k; op++) {
        i64 r, c; cin >> r >> c;
        taken[r] = true;
        taken[c] = true;
    }

    i64 rem = 0;
    for (i64 i = 1; i <= n; i++) {
        if (taken[i] == false) rem++;
    }

    i64 ans = 0;
    i64 single = 0;
    if (rem % 2 == 1) single = 1;

    for (; single <= rem; single += 2) {
        // printf("%lld: \n", single);
        // x choose single (pick who is)
        i64 choose_single = (fact[rem] * ((inv_fact[rem - single] * inv_fact[single]) % MOD)) % MOD;

        i64 to_pair = (rem - single);
        i64 others = 1;

        if (to_pair - 1 >= 0) {
            others = odd_fact[to_pair - 1] * pow2_save[to_pair / 2];
            others %= MOD;
        }

        ans += (choose_single * others) % MOD;
        ans %= MOD;
    }

    cout << ans << endl;
}

int main(void) {
    fact[0] = 1;
    odd_fact[0] = 1;
    pow2_save[0] = 1;
    inv_fact[0] = 1;

    for (i64 i = 1; i < MAX_N; i++) {
        pow2_save[i] = pow2_save[i - 1] * 2;
        pow2_save[i] %= MOD;

        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;

        odd_fact[i] = odd_fact[i - 1];
        if (i % 2 == 1) {
            odd_fact[i] *= i;
            odd_fact[i] %= MOD;
        }

        inv_fact[i] = modular_inverse(fact[i]);
    }

    int t; cin >> t;
    while (t--) {
        solve();
    }
}