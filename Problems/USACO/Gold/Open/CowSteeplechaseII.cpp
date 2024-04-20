#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
using i64 = long long;

using pt = pair<i64, i64>;

int main(void) {
    i64 N; cin >> N;

    for (i64 i = 1; i <= N; i++) {
        i64 x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        frac slope = frac(y2 - y1, x2 - x1);
        print_frac(slope);
        printf("\n");
    }
}