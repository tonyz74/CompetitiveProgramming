#include <vector>
#include <iostream>

using namespace std;

using ll = long long;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> x(m);
    for (int &i: x) {
        cin >> i;
        --i;
    }
    vector<ll> v(n + 1);
    auto dist = [&](int from, int to) {
        if (from <= to) return to - from;
        else return to + n - from;
    };
    auto add = [&](int from, int to, int num) {
        if (from <= to) {
            v[from] += num;
            v[to] -= num;
        } else {
            v[from] += num;
            v[n] -= num;
            v[0] += num;
            v[to] -= num;
        }
    };
    for (int i = 0; i < m - 1; i++) {
        add(x[i], x[i + 1], dist(x[i + 1], x[i]));
        add(x[i + 1], x[i], dist(x[i], x[i + 1]));
    }
    ll ans = 1LL << 60;
    for (int i = 0; i < n; i++) {
        v[i + 1] += v[i];
        ans = min(ans, v[i]);
    }
    cout << ans << endl;
}
