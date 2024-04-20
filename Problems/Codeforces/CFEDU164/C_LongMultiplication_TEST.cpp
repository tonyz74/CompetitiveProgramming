#include <iostream>
#include <vector>
#include <string>

using namespace std;

using i64 = long long;

void solve() {
    i64 a, b; cin >> a >> b;
    string as = to_string(a);
    string bs = to_string(b);

    i64 a_dup = a;
    i64 places = 0;
    while (a_dup > 0) {
        a_dup /= 10;
        places++;
    }

    i64 max_prod = 0;
    i64 resa = 0;
    i64 resb = 0;

    for (i64 mask = 0; mask < (1ll << places); mask++) {
        for (i64 bit = 0; bit < places; bit++) {
            if (mask & (1ll << bit)) {
                std::swap(as[bit], bs[bit]);
            }
        }

        i64 la = (i64) atoll(as.c_str());
        i64 lb = (i64) atoll(bs.c_str());

        if (la * lb > max_prod) {
            resa = la;
            resb = lb;
            max_prod = la * lb;
        }

        for (i64 bit = 0; bit < places; bit++) {
            if (mask & (1ll << bit)) {
                std::swap(as[bit], bs[bit]);
            }
        }
    }

    // printf("%lld\n%lld\n", resa, resb);
    printf("%lld\n", resa * resb);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}