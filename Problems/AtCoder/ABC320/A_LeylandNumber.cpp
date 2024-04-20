#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;

int main(void) {
    ll a, b;
    cin >> a >> b;

    ll ab = 1;
    for (int i = 0; i < b; i++) {
        ab *= a;
    }

    ll ba = 1;
    for (int i = 0; i < a; i++) {
        ba *= b;
    }

    printf("%llu\n", ab + ba);
}