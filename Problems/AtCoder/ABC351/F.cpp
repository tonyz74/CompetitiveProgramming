#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

#define MAX_N ((int) (4 * 1e5) + 7)

#define mid ((h + t) / 2)

struct segtree {
    i64 sum[MAX_N * 4];
    int cnt[MAX_N * 4];

    void update(int x) {
        sum[x] = sum[x * 2] + sum[x * 2 + 1];
        cnt[x] = cnt[x * 2] + cnt[x * 2 + 1];
    }

    void build(int x, int h, int t, const vector<i64>& a) {
        if (h == t) {
            sum[x] = a[h];
            cnt[x] = 1;
            return;
        }

        build(x * 2, h, mid, a);
        build(x * 2 + 1, mid + 1, t, a);
        update(x);
    }

    void set_to_zero(int x, int h, int t, int pos) {
        if (h == t) {
            sum[x] = 0;
            cnt[x] = 0;
            return;
        }

        if (pos <= mid) set_to_zero(x * 2, h, mid, pos);
        else set_to_zero(x * 2 + 1, mid + 1, t, pos);
        update(x);
    }

    pair<i64, int> range_get(int x, int h, int t, int h1, int t1) {
        if (h1 <= h && t <= t1) {
            return make_pair(sum[x], cnt[x]);
        }

        pair<i64, int> ans {0, 0};

        if (h1 <= mid) {
            auto get = range_get(x * 2, h, mid, h1, t1);
            ans.first += get.first;
            ans.second += get.second;
        }

        if (t1 > mid) {
            auto get = range_get(x * 2 + 1, mid + 1, t, h1, t1);
            ans.first += get.first;
            ans.second += get.second;
        }

        return ans;
    }
};

int main(void) {
    i64 N; cin >> N;

    vector<int> remap(N + 1);
    vector<i64> A(N + 1);
    vector<pair<i64, int> > S(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> A[i];

        S[i].first = A[i];
        S[i].second = i;
    }

    std::sort(S.begin() + 1, S.end());
    vector<i64> sorted_values(N + 1);

    for (int t = 1; t <= N; t++) {
        // originally was at S[t].second (i), now is at t
        remap[S[t].second] = t;
        sorted_values[t] = S[t].first;
    }

    segtree st;
    st.build(1, 1, N, sorted_values);

    i64 ans = 0;

    for (int i = 1; i <= N; i++) {
        // find first gteq
        i64 pos = std::lower_bound(
            S.begin() + 1, S.end(),
            make_pair(A[i], (int) -1e9)
        ) - S.begin();

        if (pos == 0 || pos == N + 1) {
            continue;
        }

        auto get = st.range_get(1, 1, N, pos, N);
        ans += get.first - get.second * A[i];
        st.set_to_zero(1, 1, N, remap[i]);
    }

    cout << ans << endl;
}
