// https://www.luogu.com.cn/problem/P1198

// IMPORTANT POINT (remember to ask): when asked for modulo, do you
// need it to be positive? or use negative modulus? because mathematically
// they are equivalent. i guess both are fine..

// look into MONOTONIC STACK

#include <iostream>

#define get_mid() ((h + t) / 2)

typedef long long ll;

ll M, D;
ll t = 0;
ll tree_len = 0;

#define MAXN (2 * (ll) 1e5)

ll segtree[MAXN * 4 + 10];

using namespace std;

void refresh_state(ll x) {
    segtree[x] = max(segtree[x * 2], segtree[x * 2 + 1]);
}

void update_point(ll x, ll h, ll t, ll pos, ll new_val) {
    if (t == h) {
        segtree[x] = new_val;
        return;
    }

    if (pos <= get_mid()) update_point(x * 2, h, get_mid(), pos, new_val);
    if (pos > get_mid()) update_point(x * 2 + 1, get_mid() + 1, t, pos, new_val);
    refresh_state(x);
}

ll find_max(ll x, ll h, ll t, ll h1, ll t1) {
    // printf("\nlooking for %d %d, at x of %d: ", h1, t1, x);

    if (h1 <= h && t1 >= t) {
        // fully enveloped
        // printf("skipping with a val of %d\n", segtree[x]);
        return segtree[x];
    }

    ll ret = -(D + 1);
    if (h1 <= get_mid()) ret = max(ret, find_max(x * 2, h, get_mid(), h1, t1));
    if (t1 > get_mid()) ret = max(ret, find_max(x * 2 + 1, get_mid() + 1, t, h1, t1));

    return ret;
}

int main(void) {
    cin >> M >> D;

    for (ll i = 0; i < (4 * MAXN) + 1; i++) {
        segtree[i] = -(D + 1);
    }

    for (ll i = 0; i < M; i++) {
        char ty; cin >> ty;

        if (ty == 'A') {
            ll n; cin >> n;
            n += t;
            n = ((n % D) + D) % D;

            // printf("adding n of %d\n", n);

            tree_len++;
            update_point(1, 1, MAXN, tree_len, n);
        }
        
        if (ty == 'Q') {
            ll L; cin >> L;
            // printf("\n\nmin value in %d to %d\n", tree_len - L + 1, tree_len);
            ll val = find_max(1, 1, MAXN, tree_len - L + 1, tree_len);
            t = val;

            // cout << "value was: " << val << endl;
            cout << val << endl;
        }
    }
}