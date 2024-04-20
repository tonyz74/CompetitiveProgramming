#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        int n, k; cin >> n >> k;
        if (k != 1 && k != n) {
            printf("-1\n");
        } else if (k == 1) {
            for (int j = 1; j <= n; j++) {
                printf("%d", j);
                if (j != n) printf(" ");
            }
            printf("\n");
        } else if (k == n) {
            for (int j = 1; j <= n; j++) {
                printf("1");
                if (j != n) printf(" ");
            }
            printf("\n");
        }
    }
}