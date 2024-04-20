#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using i64 = long long;

#define mid ((h + t) / 2)

struct segtree {
    i64 len;
    vector<i64> v;

    segtree(i64 n) {
        len = n;
        v.resize(4 * n + 7);
    }

    void pull(i64 x) {
        v[x] = v[x * 2] + v[x * 2 + 1];
    }

    void build(i64 x, i64 h, i64 t, const vector<i64>& iv) {
        if (h == t) {
            v[x] = iv[h];
            return;
        }

        build(x * 2, h, mid, iv);
        build(x * 2 + 1, mid + 1, t, iv);
        pull(x);
    }

    void point_update(i64 x, i64 h, i64 t, i64 pos, i64 k) {
        if (h == t) {
            v[x] += k;
            return;
        }

        if (pos <= mid) point_update(x * 2, h, mid, pos, k);
        else point_update(x * 2 + 1, mid + 1, t, pos, k);
        pull(x);
    }

    i64 range_query(i64 x, i64 h, i64 t, i64 h1, i64 t1) {
        if (h1 <= h && t <= t1) {
            return v[x];
        }

        i64 merged = 0;
        if (h1 <= mid) merged += range_query(x * 2, h, mid, h1, t1);
        if (t1 > mid) merged += range_query(x * 2 + 1, mid + 1, t, h1, t1);

        return merged;
    }
};