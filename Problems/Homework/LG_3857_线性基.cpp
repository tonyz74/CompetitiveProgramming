#include <string>
#include <iostream>

using namespace std;
using i64 = long long;

// think of this when you see some xors (two states)
struct linear_basis {
    i64 b[63];

    linear_basis() {
        memset(b, 0, sizeof(b));
    }

    void insert(i64 x) {
        for (i64 bit = 60; bit >= 0; bit--) {
            if (x & (1ll << bit)) {
                if (b[bit] != 0) {
                    x ^= b[bit];
                } else {
                    b[bit] = x;
                    return;
                }
            }
        }
    }

    i64 count() {
        i64 ans = 0;
        for (i64 i = 0; i <= 60; i++) {
            ans += b[i] != 0;
        }
        return ans;
    }
};

int main(void) {
    i64 N, M; cin >> N >> M;

    linear_basis lb;

    for (i64 i = 1; i <= M; i++) {
        string op; cin >> op;
        i64 x = 0;
        for (i64 bit = 0; bit <= 60; bit++) {
            if (op[bit] == 'X') {
                x |= (1ll << bit);
            }
        }

        lb.insert(x);
    }

    i64 in_lb = lb.count();
    cout << (1ll << in_lb) % (2008) << endl;
}