#include <iostream>
#include <vector>
using namespace std;

#define rep(name, L, R) for (int name = L; name <= R; name++)

struct cube {
    int x, y, z;
};

int ix_between(vector<cube> cubes) {
    int X_L = -1e9, X_R = 1e9;
    int Y_L = -1e9, Y_R = 1e9;
    int Z_L = -1e9, Z_R = 1e9;

    for (auto cb: cubes) {
        X_L = max(X_L, cb.x);
        X_R = min(X_R, cb.x + 7);

        Y_L = max(Y_L, cb.y);
        Y_R = min(Y_R, cb.y + 7);

        Z_L = max(Z_L, cb.z);
        Z_R = min(Z_R, cb.z + 7);
    }

    return max(X_R - X_L, 0) * max(Y_R - Y_L, 0) * max(Z_R - Z_L, 0);
}

int V1, V2, V3;

int main(void) {
    cin >> V1 >> V2 >> V3;

    int a1 = 0, b1 = 0, c1 = 0;

    rep(a2, 0, 7) rep(b2, 0, 7) rep(c2, 0, 7) {
        rep(a3, -7, 7) rep(b3, -7, 7) rep(c3, -7, 7) {
            vector<cube> cubes = {
                { .x = a1, .y = b1, .z = c1 },
                { .x = a2, .y = b2, .z = c2 },
                { .x = a3, .y = b3, .z = c3 },
            };

            int ix_3 = ix_between(cubes);

            vector<pair<int, int> > pairs = {
                {0, 1},
                {0, 2},
                {1, 2}
            };

            int ix_1 = 3 * 343;
            ix_1 -= 3 * ix_3;

            int ix_2 = 0;
            for (auto[first, second]: pairs) {
                int add = ix_between({cubes[first], cubes[second]}) - ix_3;
                ix_2 += add;
                ix_1 -= 2 * add;
            }

            if (ix_1 == V1 && ix_2 == V2 && ix_3 == V3) {
                printf("Yes\n");
                printf("0 0 0 %d %d %d %d %d %d\n", a2, b2, c2, a3, b3, c3);
                return 0;
            }
        }
    }

    printf("No\n");
}