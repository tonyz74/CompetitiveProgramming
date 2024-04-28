// JUST ROTATE INSTEAD. DON'T BE FOOLED BY AN APPARENTLY SIMPLE
// EQUATION OF MAX AND MIN AT THE START. WE WOULD RATHER HAVE ADDITION.

// NOTE: This program is incorrect.

#include <iostream>
#include <vector>
#include <algorithm>

using i64 = long long;

using namespace std;
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using i64 = long long;

#define mid ((h + t) / 2)

struct segtree {
    i64 len;
    vector<i64> v;

    segtree(i64 n) {
        len = n;
        v.resize(4 * n + 7);
    }

    void pull(i64 x) {
        v[x] = v[x * 2] + v[x * 2 + 1];
    }

    void build(i64 x, i64 h, i64 t, const vector<i64>& iv) {
        if (h == t) {
            v[x] = iv[h];
            return;
        }

        build(x * 2, h, mid, iv);
        build(x * 2 + 1, mid + 1, t, iv);
        pull(x);
    }

    void point_set_zero(i64 x, i64 h, i64 t, i64 pos) {
        if (h == t) {
            v[x] = 0;
            return;
        }

        if (pos <= mid) point_set_zero(x * 2, h, mid, pos);
        else point_set_zero(x * 2 + 1, mid + 1, t, pos);
        pull(x);
    }

    i64 range_query(i64 x, i64 h, i64 t, i64 h1, i64 t1) {
        if (h1 <= h && t <= t1) {
            return v[x];
        }

        i64 merged = 0;
        if (h1 <= mid) merged += range_query(x * 2, h, mid, h1, t1);
        if (t1 > mid) merged += range_query(x * 2 + 1, mid + 1, t, h1, t1);

        return merged;
    }
};

struct pt {
    i64 x = 0, y = 0;
    pt() {}
    pt(i64 a, i64 b): x(a), y(b) {}

    bool operator<(const pt& rhs) const {
        return make_pair(x, y) < make_pair(rhs.x, rhs.y);
    }
};

bool by_x(const pt& lhs, const pt& rhs) {
    return make_pair(lhs.x, lhs.y) < make_pair(rhs.x, rhs.y);
}

bool by_y(const pt& lhs, const pt& rhs) {
    return make_pair(lhs.y, lhs.x) < make_pair(rhs.y, rhs.x);
}

i64 calc(i64 N, vector<pt> V) {
    if (N == 0) return 0;

    i64 ans = 0;
    vector<pair<i64, pt> > diff(N + 1);

    for (i64 i = 1; i <= N; i++) {
        // y - x
        diff[i] = make_pair(V[i].y - V[i].x, V[i]);
    }

    std::sort(diff.begin() + 1, diff.end());
    vector<i64> diff_vals(N + 1);
    for (i64 i = 1; i <= N; i++) {
        diff_vals[i] = diff[i].first;
    }

    vector<i64> all_ones(N + 1, 1);

    vector<pair<pt, i64> > diff_idx(N + 1);
    for (i64 i = 1; i <= N; i++) {
        diff_idx[i].first = diff[i].second;
        diff_idx[i].second = i;
    }

    {
        segtree sums(N);
        segtree presence(N);
        presence.build(1, 1, N, all_ones);
        {
            vector<i64> x_vals(N + 1);
            for (i64 i = 1; i <= N; i++) {
                x_vals[i] = diff[i].second.x;
            }
            sums.build(1, 1, N, x_vals);
        }

        std::sort(diff_idx.begin() + 1, diff_idx.end(), [&] (const auto& a, const auto& b) {
            return by_x(a.first, b.first);
        });

        for (i64 i = 1; i <= N; i++) {
            i64 c = diff_idx[i].first.y - diff_idx[i].first.x;
            i64 srch = std::lower_bound(diff_vals.begin() + 1, diff_vals.end(), c) - diff_vals.begin();

            i64 xlen = srch - 1;
            if (xlen != 0) {
                i64 range_query = sums.range_query(1, 1, N, 1, xlen);
                i64 n_active = presence.range_query(1, 1, N, 1, xlen);
                ans += range_query - n_active * diff_idx[i].first.x;
            }
            sums.point_set_zero(1, 1, N, diff_idx[i].second);
            presence.point_set_zero(1, 1, N, diff_idx[i].second);
        }
    }

    {
        segtree sums(N);
        segtree presence(N);
        presence.build(1, 1, N, all_ones);
        {
            vector<i64> y_vals(N + 1);
            for (i64 i = 1; i <= N; i++) {
                y_vals[i] = diff[i].second.y;
            }
            sums.build(1, 1, N, y_vals);
        }

        std::sort(diff_idx.begin() + 1, diff_idx.end(), [&] (const auto& a, const auto& b) {
            return by_y(a.first, b.first);
        });

        for (i64 i = 1; i <= N; i++) {
            i64 c = diff_idx[i].first.y - diff_idx[i].first.x;
            i64 srch = std::lower_bound(diff_vals.begin() + 1, diff_vals.end(), c) - diff_vals.begin();

            i64 ylen = N - srch + 1;
            if (ylen != 0) {
                i64 range_query = sums.range_query(1, 1, N, srch, N);
                i64 n_active = presence.range_query(1, 1, N, srch, N);
                ans += range_query - n_active * diff_idx[i].first.y;
            }
            sums.point_set_zero(1, 1, N, diff_idx[i].second);
            presence.point_set_zero(1, 1, N, diff_idx[i].second);
        }
    }

    return ans;
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
