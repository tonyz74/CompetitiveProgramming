#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

ull invert_mod(ull a, ull p) {
    unsigned long long new_ = 1, old = 0, q = p, r, h;
    int pos = 0;
    while (a > 0) {
        r = q%a;
        q = q/a;
        h = q*new_ + old;
        old = new_;
        new_ = h;
        q = a;
        a = r;
        pos = !pos;
    }
    return pos ? old : (p - old);
}

#define MOD_BASE 998244353

ll N;
ll X;
ll T[1000 + 5];

// DP[i] => probability that song will switch at time i
//
// this is equal to (1/N) * (sum of DP[i - T[k]] for each k = [1, N])
//
// each song can switch at DP[i - song length], however we've calculated for N songs so
// we need to divide by N to balance that
ll DP[10000 + 5];

// ans = (1/N) * (DP[X - T1 + 1] + DP[X - T1 + 2] + ... + DP[X])

int main(void) {
    cin >> N >> X;
    for (int i = 1; i <= N; i++) cin >> T[i];

    // we can just keep multiplying by this recip_N
    ll recip_N = invert_mod(N, MOD_BASE);

    DP[0] = 1;

    for (ll i = 1; i <= X; i++) {
        ll total = 0;
        for (ll song = 1; song <= N; song++) {
            ll before = i - T[song];
            if (before >= 0) {
                total += DP[before];
                total %= MOD_BASE;
            }
        }

        DP[i] = (total * recip_N) % MOD_BASE;
    }

    ll prob = 0;
    for (ll sw = X - T[1] + 1; sw <= X; sw++) {
        if (sw < 0) continue;
        prob += DP[sw];
        prob %= MOD_BASE;
    }
    cout << ((prob * recip_N) % MOD_BASE) << endl;
}