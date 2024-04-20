#include <iostream>
#include <vector>

using namespace std;

struct rect {
    int a, b;
    rect(int A, int B) : a(A), b(B) {}
};

bool rect_cmp(rect first, rect second) {
    return (first.a == second.a && first.b == second.b) || (first.a == second.b && second.a == first.b);
}

void solve() {
    int a, b; cin >> a >> b;
    rect r_orig = rect(a, b);

    // two options:
    // half a onto half a
    int half_a = a / 2;
    if (a % 2 == 0 && half_a != 0) {
        rect r_new = rect(half_a, 2 * b);
        if (rect_cmp(r_new, r_orig) == 0) {
            printf("yes\n");
            return;
        }
    }

    int half_b = b / 2;
    if (b % 2 == 0 && half_b != 0) {
        rect r_new = rect(half_b, 2 * a);
        if (rect_cmp(r_orig, r_new) == 0) {
            printf("yes\n");
            return;
        }
    }

    printf("no\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}