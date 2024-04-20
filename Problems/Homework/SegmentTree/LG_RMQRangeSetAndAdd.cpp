#include <iostream>
#include <vector>
#include <ios>
#include <algorithm>

using namespace std;
using i64 = long long;
const i64 NONE = 1e18 + 5;

int a[(int) (1e6 + 4)];

#define mid ((h + t) / 2)

struct lz {
    i64 assign = NONE;
    i64 add = 0;
};

struct segtree {
    i64 len;
    vector<i64> v;
    vector<lz> lazy;

    segtree(i64 n) {
        len = n;
        v.resize(n * 4 + 5);
        lazy.resize(n * 4 + 5);
    }

    void update(i64 x) {
        v[x] = max(v[x * 2], v[x * 2 + 1]);
    }

    void build(i64 x, i64 h, i64 t) {
        if (h == t) {
            v[x] = a[h];
            return;
        }

        build(x * 2, h, mid);
        build(x * 2 + 1, mid + 1, t);
        update(x);
    }

    void apply_lz(i64 x, lz upd_data) {
        if (upd_data.assign != NONE) {
            lazy[x] = upd_data;
            v[x] = upd_data.assign + upd_data.add;
        } else {
            lazy[x].add += upd_data.add;
            v[x] += upd_data.add;
        }
    }

    void down(i64 x) {
        if (lazy[x].assign == NONE && lazy[x].add == 0) return;

        apply_lz(x * 2, lazy[x]);
        apply_lz(x * 2 + 1, lazy[x]);

        lazy[x].assign = NONE;
        lazy[x].add = 0;
    }

    void range_update(i64 x, i64 h, i64 t, i64 h1, i64 t1, lz upd_data) {
        // printf("%lld %lld %lld, [%lld %lld] (%lld), (%lld %lld)\n", x, h, t, h1, t1, mid, upd_data.assign, upd_data.add);

        if (h1 <= h && t <= t1) {
            // printf("direct apply\n");
            apply_lz(x, upd_data);
            return;
        }

        down(x);
        if (h1 <= mid) range_update(x * 2, h, mid, h1, t1, upd_data);
        if (t1 > mid) range_update(x * 2 + 1, mid + 1, t, h1, t1, upd_data);
        update(x);
    }

    i64 range_max(i64 x, i64 h, i64 t, i64 h1, i64 t1) {
        // printf("%lld; %lld %lld; %lld %lld\n", x, h, t, h1, t1);
        if (h1 <= h && t <= t1) {
            return v[x];
        }

        i64 ans = -1e18;

        down(x);
        if (h1 <= mid) ans = max(range_max(x * 2, h, mid, h1, t1), ans);
        if (t1 > mid) ans = max(range_max(x * 2 + 1, mid + 1, t, h1, t1), ans);
        update(x);

        return ans;
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    i64 n, q; cin >> n >> q;

    for (i64 i = 1; i <= n; i++) {
        cin >> a[i];
    }

    segtree st(n);
    st.build(1, 1, n);

    for (i64 i = 1; i <= q; i++) {
        int t; i64 L, R;
        cin >> t >> L >> R;

        if (t == 3) {
            cout << st.range_max(1, 1, n, L, R) << '\n';
        } else {
            i64 X; cin >> X;
            lz upd_packet;
            if (t == 1) upd_packet.assign = X;
            else upd_packet.add = X;
            st.range_update(1, 1, n, L, R, upd_packet);
        }
    }
}