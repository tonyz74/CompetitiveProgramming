#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctgmath>

using namespace std;

void setIO() {
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
}

struct rect {
    int left, bottom, right, top;
};

int main(void) {
    setIO();

    rect p1, p2;
    scanf("%d %d %d %d", &p1.left, &p1.bottom, &p1.right, &p1.top);
    scanf("%d %d %d %d", &p2.left, &p2.bottom, &p2.right, &p2.top);

    int min_x = min(p1.left, p2.left);
    int max_x = max(p1.right, p2.right);

    int min_y = min(p1.bottom, p2.bottom);
    int max_y = max(p1.top, p2.top);

    int max_diff = max(abs(max_y - min_y), abs(max_x - min_x));
    printf("%d\n", max_diff * max_diff);
}