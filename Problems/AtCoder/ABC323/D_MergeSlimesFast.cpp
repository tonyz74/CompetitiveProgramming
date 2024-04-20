#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

int main(void) {
    int N; cin >> N;
    vector<int> C(N + 1);
    vector<int> S(N + 1);

    map<ll, ll> slimes;

    ll total = 0;

    for (int i = 1; i <= N; i++) {
        cin >> S[i];
        cin >> C[i];

        slimes[S[i]] = C[i];
    }

    auto new_it = slimes.cbegin();
    // NOTE. TAKE.
    for (auto it = slimes.cbegin(); it != slimes.cend(); it = new_it) {
        ll to_transform = it->second / 2;
        if (to_transform != 0) {
            slimes[it->first * 2ll] += to_transform;
        }
        total += it->second % 2;

        ++new_it;
        slimes.erase(it);
    }
    
    cout << total << endl;
}