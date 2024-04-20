#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int ans = 0;
    // disjoint
    if (b <= c || d <= a) {
        ans = (b - a) + (d - c);
    } else {
        ans = max(a, max(b, max(c, d))) - min(a, min(b, min(c, d)));
    }

    printf("%d\n", ans);
}