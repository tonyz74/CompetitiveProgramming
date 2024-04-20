#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

typedef long long ll;

using p = pair<ll, ll>;

ll f(ll v, ll right) {
    return right / v;
}

ll num_values(ll v, ll actual, ll cap) {
    // careful to always remember this!
    if (cap < actual) return 0;
    ll ans = f(v, cap) - f(v, max(actual - 1, 0ll));

    // 0 is a multiple of whatever that was!
    if (actual == 0) ans++;
    return ans;
}

#define int ll

signed main(void) {
    ll n, l, r; cin >> n >> l >> r;
    vector<ll> a(n + 1);

    assert(l != r);

    ll MOD = 0;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        MOD = max(a[i], MOD);
    }

    if (MOD == 0) {
        printf("%d\n", 0);
        return 0;
    }

    // 0 - (MOD - 1)
    vector<vector<p> > graph(MOD);
    for (int node = 0; node < MOD; node++) {
        for (int j = 1; j <= n; j++) {
            int endpoint = (node + a[j]) % MOD;
            graph[node].push_back(make_pair(a[j], endpoint));
        }
    }

    priority_queue<p, vector<p>, greater<p> > pq;
    pq.push(make_pair(0, 0));

    vector<ll> shortest(MOD, 1e18);
    shortest[0] = 0;

    vector<bool> seen(MOD, false);

    while (!pq.empty()) {
        p top = pq.top();
        pq.pop();

        if (seen[top.second]) continue;
        seen[top.second] = true;

        for (p conn: graph[top.second]) {
            int val = conn.first + top.first;
            if (val < shortest[conn.second]) {
                pq.push(make_pair(val, conn.second));
                shortest[conn.second] = val;
            }
        }
    }

    ll total_b = 0;
    for (int i = 0; i < MOD; i++) {
        if (shortest[i] == 1e18) continue;
        
        ll real_left = max(l, shortest[i]);
        // be aware we want the number of numbers that are congruent to i mod MOD.
        ll diff_b = num_values(MOD, real_left - i, r - i);
        total_b += diff_b;
    }

    cout << total_b << endl;
}