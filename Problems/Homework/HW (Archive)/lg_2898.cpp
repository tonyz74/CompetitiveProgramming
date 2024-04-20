#include <iostream>
#include <algorithm>
#include <vector>

#define get_mid() ((h + t) / 2)

using namespace std;

struct stmt {
    int l, r, x;

    bool operator<(const stmt &rhs) const {
        return this->x > rhs.x;
    }
};

int N, Q;
vector<stmt> S;

// operations: add x to value, find minimum
struct segtree {
    // stores the minimum value
    vector<int> v;
    // stores value to set to
    vector<int> lazy;

    // [1, len]
    segtree(int len) {
        v.resize(4 * (len + 1) + 3, 0);
        lazy.resize(4 * (len + 1) + 3, 0);
    }

    void upd_node(int x) {
        v[x] = min(v[x * 2], v[x * 2 + 1]);
    }

    void down(int x) {
        if (lazy[x] != 0) {
            lazy[x * 2] += lazy[x];
            v[x * 2] += lazy[x];

            lazy[x * 2 + 1] += lazy[x];
            v[x * 2 + 1] += lazy[x];

            lazy[x] = 0;
        }
    }

    int find_min(int x, int h, int t, int h1, int t1) {
        if (h1 <= h && t1 >= t) {
            return v[x];
        }

        down(x);
        int res = 1e9;

        if (h1 <= get_mid()) res = min(res, find_min(x * 2, h, get_mid(), h1, t1));
        if (t1 > get_mid()) res = min(res, find_min(x * 2 + 1, get_mid() + 1, t, h1, t1));

        if (res == 1e9) {
            printf("NOT SUPPOSED TO HAPPEN\n");
            exit(-1);
        }

        return res;
    }

    void range_add(int x, int h, int t, int h1, int t1, int k) {
        if (h1 <= h && t1 >= t) {
            lazy[x] += k;
            v[x] += k;
            return;
        }

        down(x);
        if (h1 <= get_mid()) range_add(x * 2, h, get_mid(), h1, t1, k);
        if (t1 > get_mid()) range_add(x * 2 + 1, get_mid() + 1, t, h1, t1, k);
        upd_node(x);
    }
};

pair<bool, stmt> get_ix(stmt res, stmt other) {
    stmt end;
    end.l = max(res.l, other.l);
    end.r = min(res.r, other.r);

    if (end.l > end.r) return make_pair(false, stmt());
    return make_pair(true, end);
}

bool valid(int ep) {
    vector<stmt> sub(ep + 1);
    for (int i = 1; i <= ep; i++) sub[i] = S[i];
    sort(sub.begin() + 1, sub.end());

    // i want 1 based indexing
    vector<pair<stmt, stmt> > merged;
    merged.push_back({});

    // now merge everything with the same reported value

    for (int i = 1; i <= ep; i++) {
        stmt intersected = sub[i];
        stmt united = sub[i];

        // merge
        while (i + 1 <= ep && sub[i].x == sub[i + 1].x) {
            // if two separate regions say they have the same value,
            // the hay cow must be lying
            auto ans = get_ix(intersected, sub[i + 1]);
            if (ans.first == false) return false;
            intersected = ans.second;

            united.l = min(united.l, sub[i + 1].l);
            united.r = max(united.r, sub[i + 1].r);

            i++;
        }

        merged.push_back(make_pair(intersected, united));
    }

    segtree cache(N);
    for (int i = 1; i < (int) merged.size(); i++) {
        // printf("trying %d, %d -> %d\n", merged[i].l, merged[i].r, merged[i].x);
        // if there are no remaining spaces. it must be within the intersected region,
        // as we know it'll be within there
        int min_val = cache.find_min(1, 1, N, merged[i].first.l, merged[i].first.r);
        if (min_val != 0) return false;

        // we don't actually care about value because
        // we've sorted already, just being covered (nonzero) is enough.

        // this is within the united region, as the "is min value" statement
        // should still hold if there is no contradiction.
        cache.range_add(1, 1, N, merged[i].second.l, merged[i].second.r, 1);
    }

    return true;
}

int main(void) {
    cin >> N >> Q;
    S.resize(Q + 1);

    for (int i = 1; i <= Q; i++) {
        cin >> S[i].l >> S[i].r >> S[i].x;
    }

    int lo = 0;
    int hi = Q;

    while (lo < hi) {
        // round up
        int mid = (lo + hi + 1) / 2;

        if (valid(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    if (lo == Q) {
        printf("0\n");
    } else {
        printf("%d\n", lo + 1);
    }
}