// things to write about:
// tree depth is log2(N)
//
// tree can be uneven (sticks out at the end)
//
// the number of nodes corresponding to a segment is log2
//
// thus, the time complexity of finding the nodes is log2 (you only go down with one
// branch each time, except the first one, so you'll split the workload in half each time)
//
// only some operations can be done, logical AND and OR cannot

#include <vector>
#include <iostream>

using namespace std;

#define MAXN ((long long) (1e5 + 5))
typedef long long ll;

ll a[MAXN] = {0};
ll v[MAXN * 4] = {0};
ll lazy[MAXN * 4] = {0};

#define get_mid() ((h + t) / 2)

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
    if (lazy[x] != 0) {
        lazy[x * 2] += lazy[x];
        lazy[x * 2 + 1] += lazy[x];

        // add the actual values to the v array
        v[x * 2] += (get_mid() - h + 1) * lazy[x];
        v[x * 2 + 1] += (t - get_mid()) * lazy[x];

        // DONT FORGET
        lazy[x] = 0;
    }
}

void update_range(ll x, ll h, ll t, ll h1, ll t1, ll k) {
    if (h1 <= h && t1 >= t) {
        v[x] += k * (t - h + 1);
        lazy[x] += k;
        return;
    }

    lazy_propagate(x, h, t);
    if (h1 <= get_mid()) update_range(x * 2, h, get_mid(), h1, t1, k);
    if (t1 > get_mid()) update_range(x * 2 + 1, get_mid() + 1, t, h1, t1, k);
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

    return ans;
}

int main(void) {
    ll n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build_tree(1, 1, n);
    
    // do queries
    for (int i = 1; i <= m; i++) {
        int ty;
        cin >> ty;

        if (ty == 1) {
            int h, t, k;
            cin >> h >> t >> k;
            update_range(1, 1, n, h, t, k);
        } else {
            int h, t;
            cin >> h >> t;
            cout << get_range_sum(1, 1, n, h, t) << endl;
        }
    }
}