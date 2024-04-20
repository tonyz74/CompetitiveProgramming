#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_L ((int) 1e6)
#define MAX_N ((int) 1e3)
#define INF ((int) 1e9)
#define mid ((h + t) / 2)

#define HAS_COW (INF - 1)
#define INIT (INF)

// range min query segment tree
struct rmq_segtree {
    int N;
    vector<int> v;
    vector<int> lazy;

    rmq_segtree(int n) {
        N = n;
        v.resize(N * 4 + 5, INF);
        lazy.resize(N * 4 + 5, INF);
    }

    void refresh_node(int x) {
        v[x] = min(v[x * 2], v[x * 2 + 1]);
    }

    void build(int x, int h, int t) {
        if (h == t) {
            v[x] = INIT;
            return;
        }

        build(x * 2, h, mid);
        build(x * 2 + 1, mid + 1, t);
        refresh_node(x);
    }

    void lazy_propagate(int x, int h, int t) {
        if (lazy[x] != INIT) {
            // only update if it'll be used
            lazy[x * 2] = min(lazy[x * 2], lazy[x]);
            lazy[x * 2 + 1] = min(lazy[x * 2 + 1], lazy[x]);

            v[x * 2] = min(v[x * 2], lazy[x]);
            v[x * 2 + 1] = min(v[x * 2 + 1], lazy[x]);

            lazy[x] = INIT;
        }
    }

    // set everything from h1 to t1 to k
    void range_assign(int x, int h, int t, int h1, int t1, int k) {
        if (h1 <= h && t1 >= t) {
            v[x] = min(v[x], k);
            lazy[x] = min(lazy[x], k);
            return;
        }

        lazy_propagate(x, h, t);
        if (h1 <= mid) range_assign(x * 2, h, mid, h1, t1, k);
        if (t1 > mid) range_assign(x * 2 + 1, mid + 1, t, h1, t1, k);
        refresh_node(x);
    }

    int range_min(int x, int h, int t, int h1, int t1) {
        if (h1 <= h && t1 >= t) {
            return v[x];
        }

        lazy_propagate(x, h, t);
        int ans = INF;
        if (h1 <= mid) ans = min(ans, range_min(x * 2, h, mid, h1, t1));
        if (t1 > mid) ans = min(ans, range_min(x * 2 + 1, mid + 1, t, h1, t1));

        return ans;
    }
};

int N, L, A, B;

int main(void) {
    cin >> N >> L >> A >> B;

    rmq_segtree prev(L);

    for (int i = 1; i <= N; i++) {
        int S, E;
        cin >> S >> E;

        if (E - S > 1) {
            prev.range_assign(1, 1, L, S + 1, E - 1, HAS_COW);
        }
    }

    vector<int> DP(L + 2, -1);
    DP[0] = 0;

    for (int pos = 2 * A; pos <= L; pos += 2) {
        int leftbound = pos - 2 * B;
        int rightbound = pos - 2 * A;

        if (leftbound <= 0) {
            // fits within the one sprinkler distance
            DP[pos] = 1;
        } else {
            // find the best choice from before
            int rq = prev.range_min(1, 1, L, leftbound, rightbound);
            if (rq <= MAX_L) {
                // printf("found an acceptable value of %d for %d to %d (pos = %d)\n", rq, leftbound, rightbound, pos);
                DP[pos] = rq + 1;
            }
        }

        if (DP[pos] != -1 && prev.range_min(1, 1, L, pos, pos) != HAS_COW) {
            prev.range_assign(1, 1, L, pos, pos, DP[pos]);
            // printf("affirming %d's best to be %d\n", pos, DP[pos]);
        }
    }

    cout << DP[L] << endl;
};