#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long long ll;

int main(void) {
    int N; cin >> N;
    vector<int> C(N + 1);
    vector<int> S(N + 1);
    unordered_map<ll, ll> slimes;

    for (int i = 1; i <= N; i++) {
        cin >> S[i];
        cin >> C[i];

        slimes[S[i]] = C[i];
    }

    vector<ll> should_remove;
    // int iter = 0;
    int ok = true;
    while (ok) {
        // printf("\n\n");
        int modified_any = false;

        should_remove.clear();

        for (pair<ll, ll> p: slimes) {
            ll to_transmute = p.second / 2;
            if (p.second == 0) should_remove.push_back(p.first);
            
            if (to_transmute != 0) {
                // printf("changed %lld of %lld (orig %lld) into %lld of %lld\n", p.second - p.second % 2, p.first, p.second, to_transmute, p.first * 2);
                slimes[p.first * 2ll] += to_transmute;
                modified_any = true;
            }

            ll orig = p.second;
            slimes[p.first] = p.second % 2;
            // printf("setting n sz %lld to %lld (origin %d)\n", p.first, p.second, orig);
        }

        for (ll x: should_remove) slimes.erase(slimes.find(x));

        ok = modified_any;
    }

    ll n = 0;
    for (auto p: slimes) {
        n += p.second;
    }
    cout << n << endl;
}