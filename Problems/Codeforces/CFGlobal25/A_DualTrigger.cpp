#include <iostream>
#include <vector>
#include <string>

using namespace std;
using i64 = long long;

int main(void) {
    int t; cin >> t;
    while (t--) {
        i64 n; cin >> n;
        string s; cin >> s;
        i64 x = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == '1') x++;
        }

        if (x == 2 && n == 2) {
            printf("NO\n");
            continue;
        }

        if (x == 2) {
            bool has_fail = false;

            for (int i = 0; i < n - 1; i++) {
                if (s[i] == '1' && s[i + 1] == '1') {
                    has_fail = true;
                    break;
                }
            }

            if (has_fail) {
                printf("NO\n");
                continue;
            }
        }

        if (x % 2 == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}