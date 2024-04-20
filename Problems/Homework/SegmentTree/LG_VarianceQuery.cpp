#include <iostream>
#include <vector>
#include <algorithm>

#define mid ((h + t) / 2)

using namespace std;
using i64 = long long;
const i64 MOD = 1e9 + 7;

i64 a[(int) (1e5) + 7];

pair<i64, i64> merge_under_mod(pair<i64, i64> a, pair<i64, i64> b) {
    return make_pair((a.first + b.first) % MOD, (a.second + b.second) % MOD);
}

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

struct segtree {
    int len;
    vector<i64> v;
    vector<i64> v_sq;

    segtree(int n) {
        len = n;
        v.resize(n * 4 + 4);
        v_sq.resize(n * 4 + 4);
    }

    void update(int x) {
        v[x] = v[x * 2] + v[x * 2 + 1];
        v[x] %= MOD;

        v_sq[x] = v_sq[x * 2] + v_sq[x * 2 + 1];
        v_sq[x] %= MOD;
    }

    void build(int x, int h, int t) {
        if (h == t) {
            v[x] = a[h];
            v_sq[x] = (a[h] * a[h]) % MOD;
            return;
        }

        build(x * 2, h, mid);
        build(x * 2 + 1, mid + 1, t);
        update(x);
    }

    void assign(int x, int h, int t, int pos, i64 k) {
        if (h == t) {
            v[x] = k % MOD;
            v_sq[x] = (k * k) % MOD;
            return;
        }

        if (pos <= mid) assign(x * 2, h, mid, pos, k);
        else assign(x * 2 + 1, mid + 1, t, pos, k);
        update(x);
    }
    
    i64 range_variance(int L, int R) {
        auto [sum, sum_squares] = range_sums(1, 1, len, L, R);

        i64 M = (R - L + 1);
        i64 numer_lhs = (M * (sum_squares)) % MOD;
        i64 numer_rhs = (sum * sum) % MOD;
        i64 numer = ((numer_lhs - numer_rhs) % MOD + MOD) % MOD;

        i64 denom = (M * M) % MOD;
        i64 recip = modular_inverse(denom);

        return (numer * recip) % MOD;
    }

    // first -> non_squared, second -> squared
    pair<i64, i64> range_sums(int x, int h, int t, int h1, int t1) {
        if (h1 <= h && t <= t1) {
            return make_pair(v[x], v_sq[x]);
        }

        pair<i64, i64> ans = make_pair(0, 0);
        if (h1 <= mid) ans = merge_under_mod(ans, range_sums(x * 2, h, mid, h1, t1));
        if (t1 > mid) ans = merge_under_mod(ans, range_sums(x * 2 + 1, mid + 1, t, h1, t1));

        return ans;
    }
};

int main(void) {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    } 

    segtree st(n);
    st.build(1, 1, n);

    for (int i = 1; i <= q; i++) {
        int ty, x, y; cin >> ty >> x >> y;

        if (ty == 1) {
            st.assign(1, 1, n, x, y);
        } else {
            cout << st.range_variance(x, y) << endl;
        }
    }
}