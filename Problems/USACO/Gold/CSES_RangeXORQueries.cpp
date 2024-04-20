#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int n, q; cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i] = a[i - 1] ^ x; 
    }

    while (q--) {
        int x, y; cin >> x >> y;
        printf("%d\n", a[y] ^ a[x - 1]);
    }
}