#include <iostream>

using namespace std;

typedef long long ll;

int main(void) {
    ll B; cin >> B;

    for (ll A = 1; A <= 15; A++) {
        ll exp = 1;
        for (int i = 0; i < A; i++) exp *= A;

        if (exp == B) {
            printf("%lld\n", A);
            return 0;
        }
    }

    printf("-1\n");
}