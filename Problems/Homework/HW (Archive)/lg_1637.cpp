#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

#define mid ((h + t) / 2)
#define MAX_V ((ll) 1e5 + 4)
typedef long long ll;

using a3 = array<ll, 3>;

void print_a3(a3 v) {
    printf("{ %lld, %lld, %lld }", v[0], v[1], v[2]);
}

a3 combine(a3 a, a3 b) {
    a3 res = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
    return res;
}

struct segtree {
    a3 v[MAX_V * 4];

    void refresh_node(int x) {
        v[x] = combine(v[x * 2], v[x * 2 + 1]);
    }

    void build(int x, int h, int t) {
        if (h == t) {
            v[x][0] = 0;
            v[x][1] = 0;
            v[x][2] = 0;
            return;
        }

        build(x * 2, h, mid);
        build(x * 2, mid + 1, t);
        refresh_node(x);
    }

    void modify(int x, int h, int t, int p, a3 upd) {
        if (h == t && h == p) {
            v[x] = combine(v[x], upd);
            return;
        }

        if (p <= mid) modify(x * 2, h, mid, p, upd);
        else modify(x * 2 + 1, mid + 1, t, p, upd);

        refresh_node(x);
    }

    a3 sum_query(int x, int h, int t, int l, int r) {
        a3 result = {0, 0, 0};

        if (h >= l && t <= r) {
            return v[x];
        }

        if (l <= mid) {
            result = combine(result, sum_query(x * 2, h, mid, l, r));
        }
        if (r >= mid + 1) {
            result = combine(result, sum_query(x * 2 + 1, mid + 1, t, l, r));
        }

        return result;
    }
};

int main(void) {
    segtree cache;
    cache.build(1, 1, MAX_V);

    int N;
    cin >> N;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    // for (int x: A) {
        // cout << x << " ";
    // } cout << endl;

    for (int ei = 1; ei <= N; ei++) {
        // printf("?ok\n");
        a3 lt_me = {0, 0, 0};
        if (A[ei] > 1) {
            lt_me = cache.sum_query(1, 1, MAX_V, 1, A[ei] - 1);
        }
        a3 mine = { 1, 0, 0 };

        mine[1] += lt_me[0];
        mine[2] += lt_me[1];

        // printf("ok\n");
        cache.modify(1, 1, MAX_V, A[ei], mine);

        // print_a3(mine);
        // cout << endl;
    }

    cout << cache.sum_query(1, 1, MAX_V, 1, MAX_V)[2] << endl;
}