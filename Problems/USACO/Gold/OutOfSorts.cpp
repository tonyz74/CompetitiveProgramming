#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct item {
    int val;
    int vcount;
};

bool operator<(const item& lhs, const item& rhs) {
    return make_pair(lhs.val, lhs.vcount) < make_pair(rhs.val, rhs.vcount);
}

void print_array(const vector<item>& v) {
    for (item x: v) printf("%d[%d] ", x.val, x.vcount);
    printf("\n");
}

void bubble_sort(vector<item>& v) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        print_array(v);

        for (int i = 0; i <= (int) v.size() - 2; i++) {
            if (v[i + 1] < v[i]) {
                std::swap(v[i + 1], v[i]);
                sorted = false;
            }
        }

    }
}

int main(void) {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    map<int, int> n_seen;

    int N; cin >> N;
    vector<item> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i].val;
        v[i].vcount = n_seen[v[i].val]++;
    }

    vector<item> sorted_ver = v;
    std::stable_sort(sorted_ver.begin(), sorted_ver.end());

    map<item, int> locations;
    for (int i = 0; i < N; i++) {
        locations[sorted_ver[i]] = i;
    }

    int best = 0;
    int n_blocked = 0;
    
    vector<item> max_at(N + 1);
    max_at[0] = v[0];

    for (int i = 1; i < N; i++) {
        max_at[i] = max(max_at[i - 1], v[i]);
    }

    for (int i = 0; i < N; i++) {
        if (locations[v[i]] > i) {
            item biggest = max_at[locations[v[i]] - 1];
            if (v[i] < biggest) {
                n_blocked += 1;
            }
        } else {
            int dist = i - locations[v[i]];
            best = max(dist, best);
        }
    }

    best = max(best, n_blocked);

    printf("%d\n", best + 1);

    // bubble_sort(v);
}