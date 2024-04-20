#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
using i64 = long long;

// lazy segtree here
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using i64 = long long;

#define mid ((h + t) / 2)

struct lazy_segtree {
    i64 len;
    vector<i64> v;
    vector<i64> lazy;

    lazy_segtree(i64 n) {
        len = n;
        v.resize(4 * n + 7);
        lazy.resize(4 * n + 7);
    }

    void modify(i64 x, i64 update) {
        lazy[x] += update;
        v[x] += update;
    }

    void pull(i64 x) {
        v[x] = v[x * 2] + v[x * 2 + 1];
    }

    void push(i64 x) {
        if (lazy[x] == 0) return;
        modify(x * 2, lazy[x]);
        modify(x * 2 + 1, lazy[x]);
        lazy[x] = 0;
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

    void range_update(i64 x, i64 h, i64 t, i64 h1, i64 t1, i64 k) {
        if (h1 <= h && t <= t1) {
            modify(x, k);
            return;
        }

        push(x);
        if (h1 <= mid) range_update(x * 2, h, mid, h1, t1, k);
        if (t1 > mid) range_update(x * 2 + 1, mid + 1, t, h1, t1, k);
        pull(x);
    }

    i64 range_query(i64 x, i64 h, i64 t, i64 h1, i64 t1) {
        if (h1 <= h && t <= t1) {
            return v[x];
        }

        i64 merged = 0;

        push(x);
        if (h1 <= mid) merged += range_query(x * 2, h, mid, h1, t1);
        if (t1 > mid) merged += range_query(x * 2 + 1, mid + 1, t, h1, t1);

        return merged;
    }
};

struct range {
    int L, R; int i;
    bool operator<(const range& rhs) const {
        return make_pair(R, L) < make_pair(rhs.R, rhs.L);
    }
};

int main(void) {
    i64 N, Q; cin >> N >> Q;

    vector<i64> a(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }

    lazy_segtree st(N);

    // pimarily sort by R
    vector<range> queries(Q + 1);
    for (int i = 1; i <= Q; i++) {
        cin >> queries[i].L >> queries[i].R;
        queries[i].i = i;
    }

    std::sort(queries.begin() + 1, queries.end());

    vector<int> ans(Q + 1);

    map<i64, int> last_occ;
    int i = 1;
    for (int q = 1; q <= Q; q++) {
        while (i <= queries[q].R) {
            int last = last_occ[a[i]];
            // add one to all those that don't have this yet
            // printf("%d to %d\n", last + 1, i);
            st.range_update(1, 1, N, last + 1, i, 1);
            last_occ[a[i]] = i;
            i++;
        }

        ans[queries[q].i] = st.range_query(1, 1, N, queries[q].L, queries[q].L);
    }

    for (int i = 1; i <= Q; i++) {
        printf("%d\n", ans[i]);
    }
}