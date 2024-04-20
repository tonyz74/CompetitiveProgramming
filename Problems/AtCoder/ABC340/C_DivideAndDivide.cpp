#include <iostream>
#include <vector>
#include <map>

using namespace std;
using i64 = long long;

map<i64, i64> cache;

i64 UP(i64 x, i64 div) {
    if (x % div == 0) return x / div;
    return (x / div) + 1;
}

i64 DOWN(i64 x, i64 div) {
    return x / div;
}

i64 get_ans(i64 X) {
    if (X == 1) {
        return 0;
    }

    i64 original = X;
    auto f = cache.find(original);
    if (f != cache.end()) return f->second;

    if (X % 2 == 0) {
        i64 cost = 0;
        i64 pow2_mult = 0;

        while (X % 2 == 0) {
            cost += (1ll << pow2_mult) * X;
            X /= 2;
            pow2_mult++;
        }

        // printf("ans[%lld] = %lld + %lld * get_ans(%lld)\n", original, cost, 1ll << pow2_mult, X);
        cache[original] = cost + (1ll << pow2_mult) * get_ans(X);
        return cache[original];

    } else {
        // printf("ans[%lld] = %lld + get_ans(%lld) + get_ans(%lld)\n", original, X, DOWN(X, 2), UP(X, 2));
        cache[original] = X + get_ans(DOWN(X, 2)) + get_ans(UP(X, 2));
        return cache[original];
    }

    return 0;
}

int main(void) {
    i64 N;
    cin >> N;
    cout << get_ans(N) << endl;
}