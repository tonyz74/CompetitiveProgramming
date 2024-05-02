#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

struct pt {
    i64 x = 0, y = 0;
    pt() {}
    pt(i64 a, i64 b): x(a), y(b) {}

    bool operator<(const pt& rhs) const {
        return make_pair(x, y) < make_pair(rhs.x, rhs.y);
    }
};


i64 calc(i64 N, vector<pt> V) {
    if (N == 0) return 0;

    // rotate all by 45 degrees, scale by sqrt(2)
    vector<pt> rot(N + 1);
    for (i64 i = 1; i <= N; i++) {
        rot[i].x = V[i].x + V[i].y;
        rot[i].y = V[i].y - V[i].x;
    }

    vector<i64> x_vals(N + 1);
    vector<i64> y_vals(N + 1);

    for (i64 i = 1; i <= N; i++) {
        x_vals[i] = rot[i].x;
        y_vals[i] = rot[i].y;
    }

    auto work = [&] (vector<i64> in) {
        i64 res = 0;

        std::sort(in.begin() + 1, in.end());
        vector<i64> pfx(N + 1);
        for (i64 i = 1; i <= N; i++) {
            pfx[i] = pfx[i - 1] + in[i];
        }

        for (i64 i = 1; i <= N; i++) {
            i64 srch = std::lower_bound(in.begin() + 1, in.end(), in[i]) - in.begin();
            i64 n_gteq = N - srch + 1;
            i64 n_lt = N - n_gteq;

            if (n_gteq > 0) {
                res += (pfx[N] - pfx[srch - 1]) - n_gteq * in[i];
            }

            if (n_lt > 0) {
                res += n_lt * in[i] - pfx[srch - 1];
            }
        }

        return res;
    };

    // divide final answer by 4. Reason:
    // * 1/2 to correct for scale.
    // * 1/2 to correct for double-counting.
    i64 x_sum = work(x_vals) / 2;
    i64 y_sum = work(y_vals) / 2;
    // printf("%lld %lld\n", x_sum, y_sum);
    return (x_sum + y_sum) / 2;
}

int main(void) {
    i64 N; cin >> N;
    vector<pt> P(N + 1);

    i64 O = 0;
    vector<pt> odd_par(1);

    i64 E = 0;
    vector<pt> even_par(1);

    for (i64 i = 1; i <= N; i++) {
        cin >> P[i].x >> P[i].y;

        i64 s = P[i].x + P[i].y;
        if (s % 2 == 0) {
            E++;
            even_par.push_back(P[i]);
        } else {
            O++;
            odd_par.push_back(P[i]);
        }
    }

    i64 ans = 0;
    ans += calc(O, odd_par);
    ans += calc(E, even_par);

    cout << ans << endl;
}
