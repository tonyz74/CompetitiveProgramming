#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

pair<i64, i64> solve(i64 a, i64 b, i64 C) {
    auto get = [] (i64 a, i64 b, i64 C, bool a_first) {
        i64 X = 0, Y = 0;
        i64 b_extra = b - a;

        for (i64 i = 0; i <= 60; i++) {
            i64 bit = (1ll << i);

            if (a < 0 || b < 0) {
                return make_pair(-1ll, -1ll);
            }

            // 0 we skip
            if ((C & bit) == 0) continue;
            // printf("set at %lld\n", i);

            if (b_extra >= 1) {
                b_extra--;
                Y |= bit;
                b--;
            } else {

                if (a_first) {
                    if (a == b) {
                        a--;
                        X |= bit;
                    } else {
                        b--;
                        Y |= bit;
                    }
                } else {
                    if (a == b) {
                        b--;
                        Y |= bit;
                    } else {
                        a--;
                        X |= bit;
                    }
                }

            }
        }

        if (a != b) {
            return make_pair(-1ll, -1ll);
        }

        for (i64 i = 0; i < 60 && a >= 1; i++) {
            if ((X & (1ll << i)) == 0 && (Y & (1ll << i)) == 0) {
                X |= (1ll << i);
                Y |= (1ll << i);
                a--;
            }
        }

        if (a != 0 || ((X ^ Y) != C)) {
            return make_pair(-1ll, -1ll);
        }
        return make_pair(X, Y);
    };

    auto a1 = get(a, b, C, true);
    auto a2 = get(a, b, C, false);

    if (a1.first != -1) {
        return a1;
    } else if (a2.first != -1) {
        return a2;
    } else {
        printf("-1\n");
        exit(0);
    }
}

int main(void) {
    i64 a, b, C; cin >> a >> b >> C;
    if (a > b) {
        std::swap(a, b);
        auto ans = solve(a, b, C);
        printf("%lld %lld\n", ans.second, ans.first);
    } else {
        auto ans = solve(a, b, C);
        printf("%lld %lld\n", ans.first, ans.second);
    }
}