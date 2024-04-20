#include <iostream>
#include <cmath>

using namespace std;


void solve(void) {
    int l, r;
    cin >> l >> r;

    if (l == r) {
        int rt = (int) sqrt(r);

        for (int i = 2; i <= sqrt(r); i++) {
            if (r % i == 0 && i != r) {
                int div_result = r / i;
                printf("%d %d\n", i, (div_result - 1) * i);
                return;
            }
        }
    } else {
        int max_even = r;
        if (r % 2 == 1) {
            max_even--;
        }

        if (max_even > 2) {
            int div_two = max_even / 2;
            printf("%d %d\n", 2, 2 * (div_two - 1));
            return;
        }
    }

    printf("-1\n");
}

int main(void) {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        solve();
    }
}