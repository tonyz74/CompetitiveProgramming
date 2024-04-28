#include <iostream>
#include <vector>
#include <ios>
#include <iomanip>
#include <unordered_map>

using namespace std;

using i64 = long long;
using f64 = long double;

i64 A, X, Y;
unordered_map<i64, f64> cache;

i64 skips = 0;

f64 dfs(i64 N) {
    if (N == 0) {
        return 0.00;
    }

    if (cache.count(N)) {
        skips++;
        return cache[N];
    }

    f64 with_a = dfs(N / A);

    f64 roll_dice = 0.0;
    for (i64 roll = 2; roll <= 6; roll++) {
        if (roll == A) {
            roll_dice += with_a + Y;
        } else {
            roll_dice += dfs(N / roll) + Y;
        }
    }

    f64 denom = 5.0;
    roll_dice = (roll_dice + Y) / denom;

    f64 ans = min(with_a + X, roll_dice);
    cache[N] = ans;
    return ans;
}

int main(void) {
    i64 start_N; cin >> start_N;
    cin >> A >> X >> Y;

    cout << setprecision(15) << fixed;
    cout << dfs(start_N) << endl;

    cout << skips << endl;
}
