#include <iostream>

using namespace std;

typedef long long ll;

ll N, M;

#define MAX_N ((int) 1e5)
#define mid ((h + t) / 2)

struct update_data {
    ll K, D;

    update_data() { K = 0; D = 0; }
    update_data(ll k, ll d) : K(k), D(d) {}
};

ll segtree[MAX_N * 4 + 5];
update_data lazy[MAX_N * 4 + 5];
ll A[MAX_N + 5];

void refresh_node(ll x) {
    segtree[x] = segtree[x * 2] + segtree[x * 2 + 1];
}

void build(ll x, ll h, ll t) {
    if (h == t) {
        segtree[x] = A[h];
        return;
    }

    build(x * 2, h, mid);
    build(x * 2 + 1, mid + 1, t);
    refresh_node(x);
}

void apply_update(ll x, ll h, ll t, update_data upd) {
    lazy[x].D += upd.D;
    lazy[x].K += upd.K;

    ll n = (t - h + 1);
    ll sum = ((n * (2 * upd.K + (n - 1) * upd.D))) / 2;
    segtree[x] += sum;
}

void lazy_propagate(ll x, ll h, ll t) {
    // fully enveloped, it's okay
    apply_update(x * 2, h, mid, lazy[x]);

    ll dist_from_start = mid + 1 - h;
    update_data right_upd = lazy[x];
    right_upd.K += dist_from_start * right_upd.D;
    apply_update(x * 2 + 1, mid + 1, t, right_upd);

    lazy[x].K = 0;
    lazy[x].D = 0;
}

// range sum query, one query at the end (O(N))
// a is the original, b is another sequence you make (difference array)
// b[i] = a[i] - a[i - 1]
// 
// update [l, r] -> [4, 7]
// x x x y y y y x x x
// x x x N y y y N x x
// l, r + 1 are updated



// arithmetic sequence

// b[i] = a[i] - a[i - 1]
// b[l + 1] = a[l + 1] - a[l] = (a[l + 1] + k + d) - (a[l] + k) = (a[l + 1] - a[l]) + d
// b[l + 2] = b[l + 2] + d

// given b[0..N], find a[i]
// a[i] = b[i] + a[i - 1]
// a[i - 1] = b[i - 1] + a[i - 2]
// a[i] = b[i] + b[i - 1] + ... + b[0]

// sum from 0 to i (segment tree range sum)

void update_range(ll x, ll h, ll t, ll h1, ll t1, update_data upd) {
    if (h1 <= h && t1 >= t) {
        // THIS IS WEIRD: fix the update only when applying?
        update_data actual_upd = upd;
        ll dist = h - h1;
        actual_upd.K += dist * upd.D;
        apply_update(x, h, t, actual_upd);
        return;
    }

    lazy_propagate(x, h, t);
    if (h1 <= mid) update_range(x * 2, h, mid, h1, t1, upd);
    if (t1 > mid) update_range(x * 2 + 1, mid + 1, t, h1, t1, upd);

    refresh_node(x);
}

ll find_val(ll x, ll h, ll t, ll p) {
    if (h == t && h == p) return segtree[x];

    lazy_propagate(x, h, t);
    if (p <= mid) {
        return find_val(x * 2, h, mid, p);
    } else {
        return find_val(x * 2 + 1, mid + 1, t, p);
    }
}

int main(void) {
    cin >> N >> M;
    for (ll i = 1; i <= N; i++) cin >> A[i];

    build(1, 1, N);

    for (ll _m = 0; _m < M; _m++) {
        int op; cin >> op;

        if (op == 1) {
            ll L, R, K, D; cin >> L >> R >> K >> D;
            update_range(1, 1, N, L, R, update_data(K, D));
        } else {
            ll P; cin >> P;
            ll val = find_val(1, 1, N, P);
            cout << val << endl;
        }
    }
}