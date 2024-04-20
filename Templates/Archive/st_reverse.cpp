// binary split of segment tree
// 线段树上二分

#include <vector>
#include <iostream>

using namespace std;

#define MAXN ((long long) (1e5))
#define MAXV ((long long) (1e5))
typedef long long ll;

#define mid ((h + t) / 2)

int N, Q;
int a[MAXN + 2];
int v[MAXV * 4 + 2];

void update(int x) {
    v[x] = v[x * 2] + v[x * 2 + 1];
}

void modify(int x, int h, int t, int p, int k) {
    if (t == h) {
        v[x] += k;
        return;
    }

    if (p <= mid) modify(x * 2, h, mid, p, k);
    else modify(x * 2 + 1, mid + 1, t, p, k);
    update(x);
}

int find_kth_largest(int x, int h, int t, int k) {
    if (h == t) return h;

    if (v[x * 2 + 1] >= k) return find_kth_largest(x * 2 + 1, mid + 1, t, k);
    else return find_kth_largest(x * 2, h, mid, k - v[x * 2 + 1]);
}

int main(void) {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        modify(1, 1, MAXV, a[i], 1);
    }

    cin >> Q;
    for (int q = 0; q < Q; q++) {
        int op; cin >> op;
        if (op == 0) {
            int index, new_val;
            cin >> index >> new_val;

            modify(1, 1, MAXV, a[index], -1);
            modify(1, 1, MAXV, new_val, 1);

            a[index] = new_val;
        } else {
            int k; cin >> k;
            int kth = find_kth_largest(1, 1, MAXV, k);
            cout << kth << endl;
        }
    }
}