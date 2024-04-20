#include <iostream>
#include <ctgmath>

typedef long long ll;
typedef long double dbl;

using namespace std;


int main(void) {
    ll D; cin >> D;

    ll best_diff = 1e18;
    ll halfway = (ll) ceil(sqrt((dbl) D));
    for (ll x = 0; x < halfway; x++) {
        // for (ll y = 0; y < halfway; y++) {
        //     best_diff = min(best_diff, abs(x * x + y * y - D));
        //     if (best_diff == 0) {
        //         printf("%lld %lld\n", x, y);
        //         exit(0);
        //     }
        // }

        // now we can just solve for closest y, then update best value
        ll y = (ll) round(sqrt((dbl) D - x * x));
        // printf("at x = %lld, y = %lld, diff = %lld\n", x, y, x * x + y * y - D);
        best_diff = min(best_diff, abs(x * x + y * y - D));
    }

    cout << best_diff << endl;
}