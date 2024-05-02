#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <ios>
#include <algorithm>

using namespace std;

struct range {
    int l, r;
};

struct assign_op {
    int time;
    int index;
    int value;

    bool operator<(const assign_op& other) const {
        return time < other.time;
    }
};

bool range_by_r(const pair<range, int>& lhs, const pair<range, int>& rhs) {
    return make_pair(lhs.first.r, lhs.first.l) < make_pair(rhs.first.r, rhs.first.l);
}

// segment tree

#define mid ((h + t) / 2)

struct segtree {
    int len = 0;
    vector<int> v;

    segtree(int N) {
        len = N;
        v.resize(4 * N + 7);
    }

    void pull(int x) {
        v[x] = min(v[x * 2], v[x * 2 + 1]);
    }

    void build(int x, int h, int t, int init_val) {
        if (h == t) {
            v[x] = init_val;
            return;
        }

        build(x * 2, h, mid, init_val);
        build(x * 2 + 1, mid + 1, t, init_val);
        pull(x);
    }

    void point_set(int x, int h, int t, int pos, int val) {
        if (h == t) {
            v[x] = val;
            return;
        }

        if (pos <= mid) point_set(x * 2, h, mid, pos, val);
        else point_set(x * 2 + 1, mid + 1, t, pos, val);
        pull(x);
    }

    int range_min(int x, int h, int t, int h1, int t1) {
        if (h1 <= h && t <= t1) {
            return v[x];
        }

        int ans = 1e9;
        if (h1 <= mid) ans = min(ans, range_min(x * 2, h, mid, h1, t1));
        if (t1 > mid) ans = min(ans, range_min(x * 2 + 1, mid + 1, t, h1, t1));
        return ans;
    }
};

// end segment tree

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M; cin >> N >> M;

    vector<int> A(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    // nearest occurence of same value as A[i] to my right
    vector<int> X(N + 1);

    unordered_map<int, int> mp;
    for (int i = N; i >= 1; i--) {
        if (mp[A[i]] == 0) {
            X[i] = 1e9;
        } else {
            X[i] = mp[A[i]];
        }
        mp[A[i]] = i;
    }

    // offline
    vector<pair<range, int> > queries(M + 1);
    for (int i = 1; i <= M; i++) {
        cin >> queries[i].first.l >> queries[i].first.r;
        queries[i].second = i;
    }

    std::sort(queries.begin() + 1, queries.end(), range_by_r);

    vector<assign_op> to_add(1);
    for (int i = 1; i <= N; i++) {
        assign_op op;
        // can only take effect once our right hand side reaches this far
        // (won't exceed range right side bound)
        op.time = X[i];
        op.index = i;
        op.value = X[i] - i;
        to_add.push_back(op);
    }
    std::sort(to_add.begin() + 1, to_add.end());
    int tail = to_add.size();
    int head = 1;

    vector<int> answers(M + 1);
    // segtree
    segtree st(N);
    st.build(1, 1, N, 1e9);

    // vector<i64> state(N + 1, -1);

    for (int q = 1; q <= M; q++) {
        range qr = queries[q].first;

        while (head < tail && to_add[head].time <= qr.r) {
            assign_op op = to_add[head];
            st.point_set(1, 1, N, op.index, op.value);
            // state[op.index] = op.value;
            head++;
        }

        // for (i64 i = 1; i <= N; i++) {
        //     printf("%lld ", state[i]);
        // }
        // cout << endl;
        answers[queries[q].second] = st.range_min(1, 1, N, qr.l, N);
    }

    for (int i = 1; i <= M; i++) {
        if (answers[i] >= 1e9) {
            cout << -1 << endl;
        } else {
            cout << answers[i] << endl;
        }
    }
}
