#include <iostream>
#include <vector>
#include <ios>
#include <cassert>

#define mid ((h + t) / 2)

#define MAX_N ((i64) (2 * 1e5 + 3))
using namespace std;
using i64 = long long;

struct segtree {
    i64 len = 0;
    i64 v[4 * MAX_N];
    i64 lazy[4 * MAX_N];

    segtree(int n) {
        len = n;
    }

    void update(i64 x) {
        v[x] = max(v[x * 2], v[x * 2 + 1]);
    }

    void build(i64 x, i64 h, i64 t, const vector<i64>& values) {
        if (h == t) {
            v[x] = values[h];
            return;
        }

        build(x * 2, h, mid, values);
        build(x * 2 + 1, mid + 1, t, values);
        update(x);
    }

    void apply_lazy(i64 x, i64 k) {
        lazy[x] += k;
        v[x] += k;
    }

    void lazy_push(i64 x) {
        if (lazy[x] == 0) return;
        apply_lazy(x * 2, lazy[x]);
        apply_lazy(x * 2 + 1, lazy[x]);
        lazy[x] = 0;
    }

    void range_add(i64 x, i64 h, i64 t, i64 h1, i64 t1, i64 k) {
        if (h1 <= h && t <= t1) {
            apply_lazy(x, k);
            return;
        }

        lazy_push(x);
        if (h1 <= mid) range_add(x * 2, h, mid, h1, t1, k);
        if (t1 > mid) range_add(x * 2 + 1, mid + 1, t, h1, t1, k);
        update(x);
    }

    // pos of first index that has v[x] >= k
    i64 find_first(i64 x, i64 h, i64 t, i64 h1, i64 t1, i64 k) {
        if (h == t && v[x] >= k) {
            return h;
        }

        if (v[x] < k) {
            return 1e9;
        }

        lazy_push(x);

        // dont need to consider rhs
        if (v[x * 2] >= k) {
            return find_first(x * 2, h, mid, h1, t1, k);
        } else {
            return find_first(x * 2 + 1, mid + 1, t, h1, t1, k);
        }
    }

    i64 get_value_at(i64 x, i64 h, i64 t, i64 pos) {
        if (h == t) return v[x];

        lazy_push(x);
        if (pos <= mid) return get_value_at(x * 2, h, mid, pos);
        else return get_value_at(x * 2 + 1, mid + 1, t, pos);
    }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 n, q; cin >> n >> q;
    vector<i64> a(n + 1);
    vector<i64> pfx(n + 1);
    for (i64 i = 1; i <= n; i++) {
        cin >> a[i];
        pfx[i] = pfx[i - 1] + a[i];
    }

    segtree st(n);
    st.build(1, 1, n, pfx);

    for (i64 query = 1; query <= q; query++) {
        i64 pos, new_power; cin >> pos >> new_power;
        st.range_add(1, 1, n, pos, n, new_power - a[pos]);
        a[pos] = new_power;

        i64 lo = 1;
        i64 val = st.get_value_at(1, 1, n, lo);
        // printf("val: %lld\n", val);

        // for (i64 i = 1; i <= n; i++) {
        //     printf("%lld ", st.get_value_at(1, 1, n, i));
        // }
        // printf("\n");

        if (val == 0) {
            cout << 1 << endl;
            continue;
        }

        i64 times = 0;
        while (true) {
            assert(times <= 35);
            i64 next = st.find_first(1, 1, n, lo, n, val * 2ll);
            if (next == 1e9) {
                cout << -1 << endl;
                break;
            }

            i64 next_value = st.get_value_at(1, 1, n, next);
            i64 prev_value = next_value - a[next];

            if (prev_value * 2ll == next_value) {
                cout << next << endl;
                break;
            }

            lo = next;
            val = next_value;
        }
    }
}