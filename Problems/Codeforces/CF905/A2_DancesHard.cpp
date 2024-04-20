#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

using ll = long long;

void solve() {
    ll n, m; cin >> n >> m;

    vector<ll> sto(n + 1);
    for (ll i = 2; i <= n; i++) cin >> sto[i];
    // might improve sort performance? dont know
    std::sort(sto.begin() + 1, sto.end());

    vector<ll> b(n + 1);
    for (ll i = 1; i <= n; i++) cin >> b[i];
    std::sort(b.begin() + 1, b.end());

    auto ans_with = [&] (ll k) {
        vector<ll> a = sto;
        a[1] = k;
        std::sort(a.begin() + 1, a.end());

        // for (ll i = 1; i <= n; i++) {
        //     cout << a[i] << " ";
        // }
        // cout << endl;

        ll i = 1;
        ll l = 1, r = 1;

        while (r <= n) {
            if (a[i] < b[r]) {
                r++;
                i++;
            } else {
                l++;
                r++;
            }
        }

        return l - 1;
    };

    set<ll> sols;
    vector<ll> kvals = {1, m};
    for (ll k: kvals) {
        ll v = ans_with(k);
        // printf("testing %d, got %d\n", k, v);
        sols.insert(v);
    }

    if (sols.size() == 1) {
        ll ans = m * (*sols.begin());
        cout << ans << endl;
    } else {
        // there are two possible solutions, let's find the crossover point
        // lo is the first value where the solution is s2
        ll s1 = *sols.begin();
        ll s2 = *(++sols.begin());
        ll lo = 1, hi = m;

        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            ll v = ans_with(mid);
            if (v == s2) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        // there are lo cases with the second (greater) solution
        ll ans = (lo - 1) * s1 + (m - lo + 1) * s2;
        cout << ans << endl;
    }
    // cout << sols.size() << endl;
    // assert(uniq_sols.size() <= 2);
}

int main(void) {
    ll T; cin >> T;
    while (T--) solve();
}