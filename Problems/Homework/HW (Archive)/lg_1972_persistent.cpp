#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
#define MAX_N ((int) 1e6 + 10)
#define MAX_Q MAX_N
#define mid ((h + t) / 2)




#define MAX_SZ ((int) 3.3e7 + 8)

struct segtree {
    int cnt = 1;
    int v[MAX_SZ];
    int left[MAX_SZ];
    int right[MAX_SZ];
    int roots[MAX_SZ];

    void refresh(int x) {
        v[x] = v[left[x]] + v[right[x]];
    }

    void modify(int &x, int prev, int h, int t, int p, int k) {
        x = cnt++;
        v[x] = v[prev];
        left[x] = left[prev];
        right[x] = right[prev];

        if (h == t && h == p) {
            v[x] += k;
            return;
        }

        if (p <= mid) {
            modify(left[x], left[prev], h, mid, p, k);
        } else {
            modify(right[x], right[prev], mid + 1, t, p, k);
        }

        refresh(x);
    }

    int sum_query(int x, int h, int t, int l, int r) {
        if (h >= l && t <= r) {
            return v[x];
        }

        int ans = 0;
        if (l <= mid) {
            ans += sum_query(left[x], h, mid, l, r);
        }
        if (r >= mid + 1) {
            ans += sum_query(right[x], mid + 1, t, l, r);
        }

        return ans;
    }
};

int N, M;
int a[MAX_N];

segtree cache;
int previous_positions[MAX_N];
int root;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];

    for (int pos = 1; pos <= N; pos++) {
        int tmp = cache.roots[pos - 1];
        if (previous_positions[a[pos]] != 0) {
            cache.modify(tmp, cache.roots[pos - 1], 1, MAX_N, previous_positions[a[pos]], -1);
        }

        cache.modify(cache.roots[pos], tmp, 1, MAX_N, pos, 1);
        previous_positions[a[pos]] = pos;
    }

    // so nice
    cin >> M;
    for (int i = 1; i <= M; i++) {
        int l, r;
        cin >> l >> r;

        int rt = cache.roots[r];
        // printf("root for query %d is %d\n", i, rt);
        int sum_q = cache.sum_query(rt, 1, MAX_N, l, r);
        cout << sum_q << '\n';
    }
}