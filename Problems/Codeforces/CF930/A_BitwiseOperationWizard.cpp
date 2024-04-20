#include <iostream>

using namespace std;
// remember: x or x is also x!! not just 0 or x. 0 is the sole identity for xor, not or.

void solve() {
    int n; cin >> n;

    if (n == 2) {
        printf("! 0 1\n");
        return;
    }

    // first find where 0 is

    int biggest = 0;
    for (int x = 0; x < n; x++) {
        printf("? %d %d %d %d\n", biggest, biggest, x, x);
        string resp; cin >> resp;
        if (resp == "<") {
            biggest = x;
        }
    }

    // printf("biggest is %d\n", biggest);

    int other = 0;
    for (int x = 0; x < n; x++) {
        if (x == biggest) continue;
        
        // if (biggest | other) < (biggest | x), (biggest | x) might be all 1s
        printf("? %d %d %d %d\n", biggest, other, biggest, x);
        string resp; cin >> resp;

        if (resp == "<") {
            other = x;
        } else if (resp == "=") {
            // take min with current other and this one
            printf("? %d %d %d %d\n", x, x, other, other);
            string resp2; cin >> resp2;
            if (resp2 == "<") {
                other = x;
            }
        }
    }

    printf("! %d %d\n", biggest, other);
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}
