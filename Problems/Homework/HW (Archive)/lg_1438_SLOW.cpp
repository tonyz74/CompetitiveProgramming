#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
ll a[100000 + 5];

int main(void) {
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; i++) cin >> a[i];

    for (int i = 0; i < M; i++) {
        int opt; cin >> opt;

        if (opt == 1) {
            ll l, r, k, d;
            cin >> l >> r >> k >> d;

            for (int j = l - 1; j < r; j++) {
                a[j] += k;
                k += d;
            }

        } else {
            int p; cin >> p;
            cout << a[p - 1] << endl;
        }
    }

    // for (int i = 0; i < N; i++)
        // cout << a[i] << " ";
    // cout << endl;
}