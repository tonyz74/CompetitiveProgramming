#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N ((int) (5 * 1e5) + 7)
#define mid ((h + t) / 2)

struct segtree {
    int len = 0;
    vector<int> v;

    segtree(int n) {
        len = n;
        v.resize(len * 4 + 5);
    }

    void build(int x = 1, int h = 1, int t = -1) {
        if (t == -1) t = len;

        if (h == t) {
            v[x] = 0;
            return;
        }

        build(x * 2, h, mid);
        build(x * 2 + 1, mid + 1, t);
        update(x);
    }

    void update(int x) {
        v[x] = v[x * 2] + v[x * 2 + 1];
    }

    void add_freq(int pos, int val, int x = 1, int h = 1, int t = -1) {
        if (t == -1) t = len;
        // printf("[add] %d %d %d %d %d\n", pos, val, x, h, t);

        if (h == t) {
            v[x] += val;
            return;
        }

        if (pos <= mid) add_freq(pos, val, x * 2, h, mid);
        else add_freq(pos, val, x * 2 + 1, mid + 1, t);

        update(x);
    }

    int range_sum(int h1, int t1, int x = 1, int h = 1, int t = -1) {
        if (t == -1) t = len;

        // printf("[sum] %d %d, %d %d %d ", h1, t1, x, h, t);

        if (h1 <= h && t <= t1) {
            // printf("v = %d\n", v[x]);
            return v[x];
        }
        // printf("\n");

        int ans = 0;
        if (h1 <= mid) ans += range_sum(h1, t1, x * 2, h, mid);
        if (t1 >= mid + 1) ans += range_sum(h1, t1, x * 2 + 1, mid + 1, t);

        return ans;
    }
};

int main(void) {
    int n; cin >> n;
    vector<int> a(n + 1);

    vector<int> v;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    // remove all duplicates
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    }

    segtree st(v.size());
    st.build();

    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        // printf("\ni = %d\n", i);
        int sm = st.range_sum(a[i] + 1, v.size());
        // printf("%d => %d\n", a[i], sm);
        ans += sm;
        st.add_freq(a[i], 1);
    }

    cout << ans << endl;
}