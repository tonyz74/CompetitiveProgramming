#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define MAX_N ((int) (5 * 1e5) + 7)
#define mid ((h + t) / 2)

struct segtree {
    int len = 0;
    int cnt = 0;
    vector<int> v;
    vector<int> ls;
    vector<int> rs;

    segtree(int n) {
        len = n;
        // if you have a lazy segtree, the actual needed will be roughly ((1/2)) * (n * log value) 
        // but for point update its much looser, so (1/8) or so
        v.resize(8 * 1e6);
        ls.resize(8 * 1e6);
        rs.resize(8 * 1e6);
    }

    void update(int x) {
        v[x] = v[ls[x]] + v[rs[x]];
    }

    // worst case: we build log2(total value space) each time,
    // so it's n * log2(value) total capacity to resize for
    void add_freq(int pos, int val, int& x, int h = 1, int t = 1e9 + 5) {
        if (x == 0) {
            cnt++;
            x = cnt;
        }

        if (h == t) {
            v[x] += val;
            return;
        }

        if (pos <= mid) add_freq(pos, val, ls[x], h, mid);
        else add_freq(pos, val, rs[x], mid + 1, t);

        update(x);
    }

    int range_sum(int h1, int t1, int x = 1, int h = 1, int t = 1e9 + 5) {
        if (h1 <= h && t <= t1) {
            // v[0] == 0
            return v[x];
        }

        int ans = 0;
        if (h1 <= mid) ans += range_sum(h1, t1, ls[x], h, mid);
        if (t1 >= mid + 1) ans += range_sum(h1, t1, rs[x], mid + 1, t);

        return ans;
    }
};

int main(void) {
    // int n; cin >> n;
    int n = 5 * 1e5;
    vector<int> a(n + 1);

    srand(time(0));

    vector<int> v;
    for (int i = 1; i <= n; i++){
        a[i] = rand() % ((int) 1e9);
        // cin >> a[i];
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    // remove all duplicates
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    }

    segtree st(v.size());

    long long ans = 0;

    // must be some variable, we'll set this to 1
    int root = 0;

    for (int i = 1; i <= n; i++) {
        // printf("\ni = %d\n", i);
        int sm = st.range_sum(a[i] + 1, 1e9 + 7);
        // printf("%d => %d\n", a[i], sm);
        ans += sm;

        st.add_freq(a[i], 1, root);
    }

    cout << ans << endl;
    cout << st.cnt << endl;
}