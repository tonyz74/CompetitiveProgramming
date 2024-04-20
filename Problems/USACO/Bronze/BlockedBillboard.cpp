#include <iostream>
#include <cstdio>

using namespace std;

struct rect {
    int tl_x, tl_y;
    int br_x, br_y;  
};

rect read_rect() {
    rect r;
    int bl_x, bl_y, tr_x, tr_y;
    scanf("%d %d %d %d", &bl_x, &bl_y, &tr_x, &tr_y);

    r.tl_x = bl_x;
    r.tl_y = tr_y;
    r.br_x = tr_x;
    r.br_y = bl_y;

    return r;
}

int rect_area(rect r) {
    return (r.br_x - r.tl_x) * (r.tl_y - r.br_y);
}

int ix_area(rect r1, rect r2) {
    // make r1 always to the left

    if (r1.tl_x > r2.tl_x) {
        swap(r1, r2);
    }

    // completely disjoint
    if (r1.br_x <= r2.tl_x) return 0;
    if (r1.br_y > r2.tl_y || r2.br_y > r1.tl_y) return 0;

    rect ix;
    ix.tl_x = max(r1.tl_x, r2.tl_x);
    ix.tl_y = min(r1.tl_y, r2.tl_y);

    ix.br_x = min(r1.br_x, r2.br_x);
    ix.br_y = max(r1.br_y, r2.br_y);

    return rect_area(ix);
}

int main(void) {
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout);

    rect b1 = read_rect();
    rect b2 = read_rect();
    rect truck = read_rect();

    int total = rect_area(b1) + rect_area(b2);
    printf("%d\n", total - (ix_area(b1, truck) + ix_area(b2, truck)));
    return 0;
}