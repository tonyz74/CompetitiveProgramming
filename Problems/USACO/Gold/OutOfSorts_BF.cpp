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

int n_moo = 0;

void bubble_sort(vector<item>& v) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        n_moo++;
        // print_array(v);

        for (int i = 0; i <= (int) v.size() - 2; i++) {
            if (v[i + 1] < v[i]) {
                std::swap(v[i + 1], v[i]);
                sorted = false;
            }
        }

    }
}

int main(void) {
    // freopen("sort.in", "r", stdin);
    // freopen("sort.out", "w", stdout);

    map<int, int> n_seen;

    int N; cin >> N;
    vector<item> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i].val;
        v[i].vcount = n_seen[v[i].val]++;
    }

    bubble_sort(v);
    printf("%d\n", n_moo);
}