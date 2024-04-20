#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

i64 N;
bool check(i64 X) {
    i64 num_3 = X / 3;
    i64 num_5 = X / 5;
    i64 num_3_5 = X / 15;

    i64 num_moos = num_3 + num_5 - num_3_5;
    return X - num_moos >= N;
}

int main(void) {
    freopen("moobuzz.in", "r", stdin);
    freopen("moobuzz.out", "w", stdout);
    cin >> N;
    i64 lo = 1;
    i64 hi = 1e10;

    // find first true
    while (lo < hi) {
        i64 mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    
    printf("%lld\n", lo);
}