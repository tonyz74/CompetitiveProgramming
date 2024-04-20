#include <iostream>
#include <cstdio>

using namespace std;

struct rect {
    int left, bottom, right, top;

    int area() {
        return (right - left) * (top - bottom);
    }

    int width() {
        return (right - left);
    }
    
    int height() {
        return (top - bottom);
    }
};

void read_rect(rect& r) {
    scanf("%d %d %d %d", &r.left, &r.bottom, &r.right, &r.top);
}

bool disjoint(rect r1, rect r2) {
    if (r1.left >= r2.right || r2.left >= r1.right || r1.bottom >= r2.top || r2.top >= r1.bottom) {
        return false;
    }
    return true;
}

pair<rect, bool> intersect(rect r1, rect r2) {
    if (disjoint(r1, r2)) { return make_pair(r2, false); }

    rect new_r;
    new_r.left = max(r1.left, r2.left);
    new_r.top = min(r1.top, r2.top);
    new_r.right = min(r1.right, r2.right);
    new_r.bottom = max(r1.bottom, r2.bottom);

    if (new_r.bottom >= new_r.top || new_r.left >= new_r.right) {
        return make_pair(new_r, false);
    }
    return make_pair(new_r, true);
}

int main(void) {
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout);

    rect lawnmower, feed;
    read_rect(lawnmower);
    read_rect(feed);

    pair<rect, bool> ix = intersect(lawnmower, feed);
    if (ix.second == false) {
        printf("%d\n", lawnmower.area());
    } else {
        // printf("%d %d, %d %d\n", ix.first.left, ix.first.bottom, ix.first.right, ix.first.top);
        rect ix_r = ix.first;
        int original = lawnmower.area();
        
        // only accept if same size and not in middle
        if (ix_r.width() == lawnmower.width() && (ix_r.bottom == lawnmower.bottom || ix_r.top == lawnmower.top)) {
            original -= ix_r.area();
        } else if (ix_r.height() == lawnmower.height() && (ix_r.left == lawnmower.left || ix_r.right == lawnmower.right)) {
            original -= ix_r.area();
        }

        printf("%d\n", original);
    }
}