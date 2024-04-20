#include <iostream>
#include <vector>

using namespace std;

#define mid ((h + t) / 2)

using i64 = long long;

struct div_segment_tree {
    vector<i64> v;

    div_segment_tree(i64 n) {
        v.resize(n * 4 + 4);
    }

    void range_divide(i64 x, i64 h, i64 t, i64 h1, i64 t1, i64 k) {
        if (k == 1 || v[x] == 0) return;

        if (h == t) {
            v[x] /= 2;
            return;
        }

        // don't need to care about within range or not
        if (h1 <= mid) range_divide(x * 2, h, mid, h1, t1, k);
        if (t1 >= mid + 1) range_divide(x * 2 + 1, mid + 1, t, h1, t1, k);
        update(x);
    }

    i64 range_sum(i64 x, i64 h, i64 t, i64 h1, i64 t1) {
        if (h1 <= h && t <= t1) {
            return v[x];
        }

        i64 s = 0;
        if (h1 <= mid) s += range_sum(x * 2, h, mid, h1, t1);
        if (t1 >= mid + 1) s += range_sum(x * 2 + 1, mid + 1, t, h1, t1);

        return s;
    }

    void build_tree(i64 x, i64 h, i64 t, const vector<i64>& a) {
        if (h == t) {
            v[x] = a[h];
            return;
        }

        build_tree(x * 2, h, mid, a);
        build_tree(x * 2 + 1, mid + 1, t, a);

        update(x);
    }

    void update(i64 x) {
        v[x] = v[x * 2] + v[x * 2 + 1];
    }
};

int main(void) {
    i64 N; cin >> N;
    vector<i64> A(N + 1);

    for (i64 i = 1; i <= N; i++) {
        cin >> A[i];
    }

    div_segment_tree st(N);
    st.build_tree(1, 1, N, A);

    i64 Q; cin >> Q;
    for (i64 q = 1; q <= Q; q++) {
        i64 t; cin >> t;
        i64 l, r; cin >> l >> r;

        // range divide
        if (t == 1) {
            st.range_divide(1, 1, N, l, r, 2);
        } else {
            cout << st.range_sum(1, 1, N, l, r) << endl;
        }
    }
}