#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

void solve() {
    i64 n; cin >> n;
    vector<i64> a(n + 1);

    for (i64 i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<i64> prefix_xor(n + 1);
    for (i64 i = 1; i <= n; i++) {
        prefix_xor[i] = prefix_xor[i - 1] ^ a[i];
    }

    auto f = [&] (i64 l, i64 r) {
        return prefix_xor[r] ^ prefix_xor[l - 1];
    };

    // i64 tot = 0;
    i64 triples = 0;

    // vector<int> mapping(n + 1);

    for (i64 x = 1; x <= n; x++) {
        for (i64 z = x; z <= n; z++) {
            for (i64 y = x; y <= z; y++) {
                // tot++;
                if ((f(x, y) ^ f(y, z)) > f(x, z)) {
                    // printf("%lld %lld %lld\n", x, y, z);
                    triples++;
                    // mapping[y]++;
                }
            }
        }
    }

    // for (int i = 1; i <= n; i++) {
    //     printf("y = %d => %d\n", i, mapping[i]);
    // }
    // cout << tot << " " << triples << endl;
    cout << triples << endl;
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}