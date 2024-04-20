#include <iostream>
#include <vector>

using namespace std;

void solve() {
    int n; cin >> n;

    vector<int> a(n + 1);
    vector<int> b(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[a[i]] = i;
    }

    if (n == 1) {
        printf("0\n");
        return;
    }

    vector<bool> in_order(n + 1, 0);
    int i, j; 
    int mn, mx;
    if (n % 2 == 1) {
        in_order[n / 2 + 1] = true;
        i = n / 2;
        j = n / 2 + 2;
        mn = b[n / 2 + 1]; mx = b[n / 2 + 1];
    } else {
        i = n / 2;
        j = n / 2 + 1;
        mn = b[i]; mx = b[j];
    }

    while (i != 0 && j != n + 1) {
        if (mn <= mx && b[i] <= mn && b[j] >= mx) {
            in_order[i] = true;
            in_order[j] = true;
            mn = b[i];
            mx = b[j];
        } else {
            // are you fucking kidding me break your loops you dumbass
            break;
        }

        i--;
        j++;
    }

    int n_zeroes = 0;
    for (int i = 1; i <= n; i++) {
        n_zeroes += (1 - in_order[i]);
        // printf("%d ", (int) in_order[i]);
    }
    // printf("\n");
    printf("%d\n", n_zeroes / 2);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}