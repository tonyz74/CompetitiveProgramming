#include <iostream>

using namespace std;

typedef long long ll;

struct rect {
    ll left, right, top, bottom;

    ll area() {
        return (right - left) * (top - bottom);
    }
};

rect read_rect() {
    rect r;
    scanf("%lld %lld %lld %lld", &r.left, &r.bottom, &r.right, &r.top);
    return r;
}

pair<rect, bool> intersect(rect r1, rect r2) {
    rect ix;
    ix.top = min(r1.top, r2.top);
    ix.bottom = max(r1.bottom, r2.bottom);
    ix.left = max(r1.left, r2.left);
    ix.right = min(r1.right, r2.right);

    if (ix.right <= ix.left || ix.top <= ix.bottom) return make_pair(r1, false);
    return make_pair(ix, true);
}

int main(void) {
    rect white = read_rect();
    rect b1 = read_rect(), b2 = read_rect();

    ll total = white.area();

    auto b1_res = intersect(white, b1);
    if (b1_res.second) {
        total -= b1_res.first.area();
    }

    auto b2_res = intersect(white, b2);
    if (b2_res.second) {
        total -= b2_res.first.area();
    }

    auto b_comb = intersect(b1, b2);
    if (b_comb.second) {
        auto b_comb_res = intersect(white, b_comb.first);
        if (b_comb_res.second) {
            total += b_comb_res.first.area();
        }
    }

    if (total != 0) printf("YES\n"); else printf("NO\n");
}