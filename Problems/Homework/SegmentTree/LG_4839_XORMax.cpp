#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
using i64 = long long;
const i64 MAX_BIT = 30;

#define mid ((h + t) / 2)

struct linear_basis {
    i64 b[MAX_BIT + 1];

    linear_basis() {
        memset(b, 0, sizeof(b));
    }

    void insert(i64 x) {
        for (i64 bit = MAX_BIT; bit >= 0; bit--) {
            if (x & (1ll << bit)) {
                if (b[bit] != 0) {
                    x ^= b[bit];
                } else {
                    b[bit] = x;
                    return;
                }
            }
        }
    }

    i64 count() {
        i64 ans = 0;
        for (i64 i = 0; i <= MAX_BIT; i++) {
            ans += b[i] != 0;
        }
        return ans;
    }

    i64 max_xor() {
        i64 ans = 0;
        for (i64 i = MAX_BIT; i >= 0; i--) {
            if ((ans ^ b[i]) > ans) {
                ans ^= b[i]; 
            }
        }

        return ans;
    }
};

linear_basis combine(const linear_basis& x, const linear_basis& y) {
    linear_basis res = x;
    for (i64 i = 0; i <= MAX_BIT; i++) {
        res.insert(y.b[i]);
    }
    return res;
}

const i64 MAX_N = 5 * 1e4 + 5;

struct segtree {
    i64 len = 0;
    linear_basis v[MAX_N * 4];

    segtree(i64 N) {
        len = N;
    }

    void update(i64 x) {
        v[x] = combine(v[x * 2], v[x * 2 + 1]);
    }

    void insert_ball(i64 x, i64 h, i64 t, i64 pos, i64 k) {
        if (h == t) {
            v[x].insert(k);
            return;
        }

        if (pos <= mid) insert_ball(x * 2, h, mid, pos, k);
        else insert_ball(x * 2 + 1, mid + 1, t, pos, k);
        update(x);
    }

    i64 range_xor_max(i64 L, i64 R) {
        linear_basis res;
        __range_xor_max(1, 1, len, L, R, res);
        return res.max_xor();
    }

    void __range_xor_max(i64 x, i64 h, i64 t, i64 h1, i64 t1, linear_basis& res) {
        if (h1 <= h && t <= t1) {
            res = combine(res, v[x]);
            return;
        }

        if (h1 <= mid) __range_xor_max(x * 2, h, mid, h1, t1, res);
        if (t1 > mid) __range_xor_max(x * 2 + 1, mid + 1, t, h1, t1, res);
    }
};


int main(void) {
    i64 Q, N; cin >> Q >> N;
    segtree st(N);
    for (i64 query = 0; query < Q; query++) {
        i64 type, x, y; cin >> type >> x >> y;

        if (type == 1) {
            st.insert_ball(1, 1, N, x, y);
        } else {
            cout << st.range_xor_max(x, y) << endl;
        }
    }
}