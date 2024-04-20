#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
#define MAX_N ((int) 1e6 + 10)
#define MAX_Q MAX_N
#define mid ((h + t) / 2)

#define MAX_SZ ((int) 1e7)

struct segtree {
    int cnt = 1;
    int v[MAX_SZ];
    int left[MAX_SZ];
    int right[MAX_SZ];

    void refresh(int x) {
        v[x] = v[left[x]] + v[right[x]];
    }

    void modify(int &x, int h, int t, int p, int k) {
        // if i am a zero and i have been accessed, i need a new label
        if (x == 0) {
            x = cnt++;
        }

        if (h == t && h == p) {
            v[x] += k;
            return;
        }

        if (p <= mid) {
            modify(left[x], h, mid, p, k);
        } else {
            modify(right[x], mid + 1, t, p, k);
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

struct query {
    int start, end;
    int id;
};

int responses[MAX_Q];

vector<query> queries;

bool cmp(query q1, query q2) {
    return q1.end < q2.end;
}

segtree cache;
unordered_map<int, int> previous_positions;
int root;

int main(void) {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    
    cin >> M;
    queries.resize(M + 1);
    for (int i = 1; i <= M; i++) {
        cin >> queries[i].start >> queries[i].end;
        queries[i].id = i;
    }

    sort(queries.begin() + 1, queries.end(), cmp);

    int pos = 1;
    for (int i = 1; i <= M; i++) {
        while (pos <= queries[i].end) {
            if (previous_positions[a[pos]] != 0) {
                // printf("subbed 1 from %d\n", pos);
                cache.modify(root, 1, MAX_N, previous_positions[a[pos]], -1);
            }

            // printf("added 1 to %d\n", pos);
            cache.modify(root, 1, MAX_N, pos, 1);
            previous_positions[a[pos]] = pos;
            pos++;
        }

        // now eq to the query
        responses[queries[i].id] =
            cache.sum_query(1, 1, MAX_N, queries[i].start, queries[i].end);
    }

    for (int i = 1; i <= M; i++) {
        cout << responses[i] << endl;
    }
}