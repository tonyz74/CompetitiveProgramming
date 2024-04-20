#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

ll subtree_dist(ll N, ll X, ll K) {
    if (X > N) {
        return 0;
    }
    
    if (K == 0) {
        return 1;
    }

    // disregard impossible, overflow-inducing cases
    ll current_layer = (ll) log2(X);
    if (current_layer + K > 61) {
        return 0;
    }

    ll left = X * (1ll << K);
    ll right = left + ((1ll << K) - 1);

    if (N < left) {
        return 0;
    }

    return min(N - left + 1, right - left + 1);
}

void solve() {
    ll N, X, K;
    cin >> N >> X >> K;

    ll total = subtree_dist(N, X, K);

    ll k = K;
    ll x = X;

    while (k != 0 && x != 1) {
        ll new_x = 1;
        if (x % 2 == 0) {
            new_x = x / 2;
        } else {
            new_x = (x - 1) / 2;
        }

        ll above = subtree_dist(N, new_x, k - 1);
        if (k >= 2) {
            above -= subtree_dist(N, x, k - 2);
        }
        
        k--;
        x = new_x;
        total += above;
    }

    cout << total << endl;
}

int main(void) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) solve();
}