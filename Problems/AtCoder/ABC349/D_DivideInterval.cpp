#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

int main(void) {
    i64 L, R; cin >> L >> R;

    vector<pair<i64, i64> > choices;

    while (L < R) {
        i64 pick = 0;
        i64 j = L;

        for (i64 pw = 0; pw <= 60; pw++) {
            i64 p2 = (1ll << pw);
            i64 jtest = L / p2;

            // printf("%lld %lld\n", p2, jtest);
            if (L % p2 != 0 || p2 * (jtest + 1) > R) {
                break;
            }

            pick = pw;
            j = jtest;
        }
        // printf("(%lld %lld) chose: %lld %lld\n", L, R, pick, j);

        choices.push_back({L, (1ll << pick) * (j + 1)});
        L = (1ll << pick) * (j + 1);
    }

    cout << choices.size() << endl;
    for (auto p: choices) {
        printf("%lld %lld\n", p.first, p.second);
    }
}