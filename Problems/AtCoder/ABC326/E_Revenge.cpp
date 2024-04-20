#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

ll invert_mod(ll a, ll p) {
    unsigned long long new_ = 1, old = 0, q = p, r, h;
    int pos = 0;
    while (a > 0) {
        r = q%a;
        q = q/a;
        h = q*new_ + old;
        old = new_;
        new_ = h;
        q = a;
        a = r;
        pos = !pos;
    }
    return pos ? old : (p - old);
}

#define MOD_BASE 998244353

int main(void) {
    ll average = 0;

    ll N; cin >> N;
    ll inv = invert_mod(N, MOD_BASE); // 1/N

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    // starts off with 1/N chance to land on first value
    ll prob = inv;

    for (int y = 1; y <= N; y++) {
        // ### Add to weighted avg.

        // total => weighted average
        // total += my probability * my value;
        average += (A[y] * prob);
        average %= MOD_BASE;

        // ### Transition to include landing on this y as part of prob.

        // all ways to get to any x smaller than y, since they
        // all have a 1/N chance to get to y.
        prob += (prob * inv);
        prob %= MOD_BASE;
    }

    cout << average << endl;
}