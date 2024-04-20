#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

int main(void) {
    i64 n, k; cin >> n >> k;
    i64 l; cin >> l;
    i64 take = 0;
    vector<i64> prices(l + 1);
    
    for (i64 i = 1; i <= l; i++) cin >> prices[i];

    for (i64 i = 1; i <= l; i++) {
        i64 max_take = n / prices[i];
        n -= max_take * prices[i];

        take += max_take;
    }

    assert(k == take);
    printf("OK\n");
}