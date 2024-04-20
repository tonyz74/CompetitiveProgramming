#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;
using i64 = long long;

struct rect {
    i64 top = 0;
    i64 bottom = 0;
    i64 right = 0;
};

struct vtx {
    i64 x = 0;
    i64 y = 0;

    vtx() {}
    vtx(i64 xc, i64 yc): x(xc), y(yc) {}
};

i64 K1 = 0;
i64 K2 = 0;

bool cmp_tr(vtx tr1, vtx tr2) {
    // we want big right x to come first
    return make_pair(K2 * tr1.y + K1 * tr1.x, tr1.x) > make_pair(K2 * tr2.y + K1 * tr2.x, tr2.x);
}

bool cmp_br(vtx br1, vtx br2) {
    return make_pair(K2 * br1.y - K1 * br1.x, -br1.x) < make_pair(K2 * br2.y - K1 * br2.x, -br2.x);
}

i64 least_steep_positive(const multiset<i64>& choices) {
    assert(choices.size() >= 1);
    auto lb = choices.lower_bound(0);
    if (lb == choices.end()) return 0;
    assert(lb != choices.end());
    return *lb;
}

i64 least_steep_negative(const multiset<i64>& choices) {
    assert(choices.size() >= 1);

    auto lb = choices.lower_bound(0);
    if (lb == choices.end()) {
        return *choices.rbegin();
    }

    if (lb == choices.begin()) return 0;
    assert(lb != choices.begin());
    lb--;
    return *lb;
}

void solve() {
    i64 N, X1;
    cin >> N >> X1;

    vector<vtx> tr_verts(1);
    vector<vtx> br_verts(1);
    vector<i64> others(1);

    vector<rect> rects(N + 1);
    for (i64 i = 1; i <= N; i++) {
        cin >> rects[i].bottom >> rects[i].top >> rects[i].right;
        tr_verts.push_back(vtx(rects[i].right, rects[i].top));
        br_verts.push_back(vtx(rects[i].right, rects[i].bottom));
        others.push_back(rects[i].bottom);
        others.push_back(rects[i].top);
    }

    std::sort(tr_verts.begin() + 1, tr_verts.end(), cmp_tr);
    std::sort(br_verts.begin() + 1, br_verts.end(), cmp_br);

    i64 n_neg = 0;
    i64 n_pos = 0;

    vector<i64> slopes(4 * N + 4);
    multiset<i64> positive_slopes_save;
    multiset<i64> negative_slopes_save;

    for (i64 i = 1; i <= 4 * N; i++) {
        cin >> slopes[i];
        
        if (slopes[i] < 0) negative_slopes_save.insert(slopes[i]);
        else positive_slopes_save.insert(slopes[i]);

        if (slopes[i] < 0) n_neg++;
        else n_pos++;
    }

    if (n_neg < N || n_pos < N) {
        printf("-1\n");
        return;
    }

    // for the rest, we can select greedily, give the highest one
    // the most positive slope, the bottommost one the most negative slope
    std::sort(others.begin(), others.end());

    i64 ans = 1e18;

    for (i64 first = 200; first <= 1000; first += 100) for (i64 second = 200; second <= 1000; second += 100) {
        K1 = first;
        K2 = second;
    {
        multiset<i64> positive_slopes = positive_slopes_save;
        multiset<i64> negative_slopes = negative_slopes_save;

        i64 highest = 0;
        i64 lowest = 0;

        for (i64 i = 1; i <= N; i++) {
            // biggest one would be least negative
            i64 cho = *negative_slopes.rbegin();
            negative_slopes.erase(negative_slopes.find(cho));

            highest = max(highest, tr_verts[i].y + abs(cho) * tr_verts[i].x);

            // printf("giving them %lld\n", cho);
            // printf("%lld %lld\n", tr_verts[i].x, tr_verts[i].y);
        }

        // printf("\nbottom right\n");
        for (i64 i = 1; i <= N; i++) {
            i64 cho = *positive_slopes.begin();
            positive_slopes.erase(positive_slopes.find(cho));
            lowest = min(lowest, br_verts[i].y - abs(cho) * br_verts[i].x);

            // printf("giving them %lld\n", cho);
            // printf("%lld %lld\n", br_verts[i].x, br_verts[i].y);
        }

        // printf("alive\n");


        // printf("%d %d\n", (int) positive_slopes.size(), (int) negative_slopes.size());

        // iterating in increasing order, so we want low to get big negatives
        for (i64 i = 1; i <= 2 * N; i++) {
            i64 pt = others[i];

            // can only assign positive slopes
            if (negative_slopes.empty()) {
                // we want small positives, as we're not at the top
                i64 cho = *positive_slopes.begin();
                // printf("giving a positive %lld\n", cho);
                positive_slopes.erase(positive_slopes.find(cho));
                lowest = min(lowest, pt - abs(cho) * X1);
            } else {
                // we want very negative slopes, as we're low
                i64 cho = *negative_slopes.begin();
                // printf("giving a negative %lld\n", cho);
                negative_slopes.erase(negative_slopes.find(cho));
                highest = max(highest, pt + abs(cho) * X1);
            }
        }

        ans = min(ans, highest - lowest);
    }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}