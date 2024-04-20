// mandate that addition will always happen second

#include <vector>
#include <iostream>

using namespace std;

#define MAXN ((long long) (1e5 + 5))
typedef long long ll;

ll MOD;

struct update_data {
    ll add;
    ll mult;

    update_data() {
        add = 0;
        mult = 1;
    }

    update_data(ll a, ll m) {
        add = a;
        mult = m;
    }
};

ll a[MAXN] = {0};
ll v[MAXN * 4] = {0};
update_data lazy[MAXN * 4];

#define get_mid() ((h + t) / 2)

// two things to do:
// 1. how to propagate lazy and v (predefined order of ops, need to apply immediately on range, need to stack for lazy)
// 2. how to combine two answers (max, sum, gcd, ...)

// you must be able to hold valid states for v and lazy when you combine
// operations. in all, you must be able to implement this apply_update function
// for different update data.
void apply_update(int x, int h, int t, update_data upd) {
    lazy[x].mult *= upd.mult;
    lazy[x].add *= upd.mult;
    lazy[x].add += upd.add;
    lazy[x].mult %= MOD;
    lazy[x].add %= MOD;

    v[x] *= upd.mult;
    v[x] %= MOD;
    v[x] += (t - h + 1) * upd.add;
    v[x] %= MOD;
}

void update(ll x) {
    v[x] = v[x * 2] + v[x * 2 + 1];
}

void build_tree(ll x, ll h, ll t) {
    if (h == t) {
        v[x] = a[h];
        return;
    }

    build_tree(x * 2, h, get_mid());
    build_tree(x * 2 + 1, get_mid() + 1, t);
    update(x);
}

void lazy_propagate(ll x, ll h, ll t) {
    if (lazy[x].add != 0 || lazy[x].mult != 1) {
        apply_update(x * 2, h, get_mid(), lazy[x]);
        apply_update(x * 2 + 1, get_mid() + 1, t, lazy[x]);

        // DONT FORGET
        lazy[x].add = 0;
        lazy[x].mult = 1;
    }
}

void update_range(ll x, ll h, ll t, ll h1, ll t1, update_data upd) {
    if (h1 <= h && t1 >= t) {
        apply_update(x, h, t, upd);
        return;
    }

    lazy_propagate(x, h, t);
    if (h1 <= get_mid()) update_range(x * 2, h, get_mid(), h1, t1, upd);
    if (t1 > get_mid()) update_range(x * 2 + 1, get_mid() + 1, t, h1, t1, upd);
    update(x);
}

ll get_range_sum(ll x, ll h, ll t, ll h1, ll t1) {
    if (h1 <= h && t1 >= t) {
        ll result = v[x];
        return result;
    }

    lazy_propagate(x, h, t);
    ll ans = 0;
    if (h1 <= get_mid()) ans += get_range_sum(x * 2, h, get_mid(), h1, t1);
    if (t1 > get_mid()) ans += get_range_sum(x * 2 + 1, get_mid() + 1, t, h1, t1);
    ans %= MOD;

    return ans;
}

int main(void) {
    ll n, q;
    cin >> n >> q >> MOD;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build_tree(1, 1, n);
    
    // do queries
    for (int i = 1; i <= q; i++) {
        int ty;
        cin >> ty;

        if (ty == 1 || ty == 2) {
            int h, t, k;
            cin >> h >> t >> k;

            update_data upd = (ty == 1) ? update_data(0, k % MOD) : update_data(k % MOD, 1);
            update_range(1, 1, n, h, t, upd);
        } else {
            int h, t;
            cin >> h >> t;
            cout << get_range_sum(1, 1, n, h, t) << endl;
        }
    }
}