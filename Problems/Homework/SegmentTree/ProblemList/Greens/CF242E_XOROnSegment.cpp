#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

struct range_bits {
    int occ_bit[20];

    range_bits() {
        for (i64 bit = 0; bit < 20; bit++) {
            occ_bit[bit] = 0;
        }
    }

    range_bits(i64 k) {
        for (i64 bit = 0; bit < 20; bit++) {
            if (k & (1ll << bit)) {
                occ_bit[bit] = 1;
            } else {
                occ_bit[bit] = 0;
            }
        }
    }

    i64 get_range_sum(void) {
        i64 ans = 0;
        for (i64 bit = 0; bit < 20; bit++) {
            ans += occ_bit[bit] * (1ll << bit);
        }

        return ans;
    }

    void xor_all(i64 k, int range_size) {
        for (i64 bit = 0; bit < 20; bit++) {
            if (k & (1ll << bit)) {
                occ_bit[bit] = range_size - occ_bit[bit];
            }
        }
    }

    static range_bits from_merge(const range_bits& lhs, const range_bits& rhs) {
        range_bits dup;

        for (i64 bit = 0; bit < 20; bit++) {
            dup.occ_bit[bit] += lhs.occ_bit[bit] + rhs.occ_bit[bit];
        }

        return dup;
    }
};

#define mid ((h + t) / 2)

struct lazy_segtree {
    // must store them as separate bits
    vector<range_bits> a;
    // lazy prop can just xor upon xor, it is commutative
    vector<int> lazy;

    lazy_segtree(int n) {
        a.resize(4 * n + 7);
        lazy.resize(4 * n + 7);
    }

    void push_down(int x, int h, int t) {
        if (lazy[x] != 0) {
            a[x * 2].xor_all(lazy[x], (mid - h + 1));
            lazy[x * 2] ^= lazy[x];

            a[x * 2 + 1].xor_all(lazy[x], (t - (mid + 1) + 1));
            lazy[x * 2 + 1] ^= lazy[x];

            lazy[x] = 0;
        }
    }

    void pull_up(int x) {
        a[x] = range_bits::from_merge(a[x * 2], a[x * 2 + 1]);
    }

    void build(int x, int h, int t, const vector<i64>& src) {
        if (h == t) {
            a[x] = range_bits(src[h]);
            return;
        }

        build(x * 2, h, mid, src);
        build(x * 2 + 1, mid + 1, t, src);

        pull_up(x);
    }

    i64 range_query_sum(int x, int h, int t, int h1, int t1) {
        if (h1 <= h && t <= t1) {
            return a[x].get_range_sum();
        }

        i64 ans = 0;
        push_down(x, h, t);
        if (h1 <= mid) ans += range_query_sum(x * 2, h, mid, h1, t1);
        if (t1 > mid) ans += range_query_sum(x * 2 + 1, mid + 1, t, h1, t1);
        return ans;
    }

    void range_apply_xor(int x, int h, int t, int h1, int t1, int k) {
        if (h1 <= h && t <= t1) {
            a[x].xor_all(k, t - h + 1);
            lazy[x] ^= k;
            return;
        }

        push_down(x, h, t);
        if (h1 <= mid) range_apply_xor(x * 2, h, mid, h1, t1, k);
        if (t1 > mid) range_apply_xor(x * 2 + 1, mid + 1, t, h1, t1, k);
        pull_up(x);
    }
};

int main(void) {
    i64 N; cin >> N;
    vector<i64> src(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> src[i];
    }

    lazy_segtree st(N);
    st.build(1, 1, N, src);

    i64 Q; cin >> Q;
    for (i64 qi = 1; qi <= Q; qi++) {
        int ty; cin >> ty;
        int l, r; cin >> l >> r;

        if (ty == 1) {
            cout << st.range_query_sum(1, 1, N, l, r) << endl;
        } else {
            int k; cin >> k;
            st.range_apply_xor(1, 1, N, l, r, k);
        }
    }
}
