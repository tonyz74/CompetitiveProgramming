#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int ans(const vector<int> &v) {
    map<int, int> n_times;
    for (int x: v) {
        n_times[x]++;
    }

    pair<int, int> max_p = {-1, -1};
    for (pair<int, int> p: n_times) {
        if (p.second > max_p.second) {
            max_p = p;
        }
    }

    return ((int) v.size()) - max_p.second;
}

int main(void) {
    int n; cin >> n;
    int q; cin >> q;
    (void) q;

    map<int, int> left;
    map<int, int> right;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];

        if (left[a[i]] == 0) left[a[i]] = i;
        right[a[i]] = i;
    }

    // partition into blocks, if already split well, disregard
    // final answer is sum of answers in blocks
    vector<vector<int> > blocks;

    int current = -1;
    vector<int> accum;
    for (int i = 0; i < n; i++) {
        accum.push_back(a[i]);
        // printf("i = %d\n", i);

        // opening a new region with value a[i]
        if (current != a[i]) {
            if (current == -1 || right[a[i]] >= right[current]) {
                // printf("setting current to %d\n", a[i]);
                current = a[i];
            }
        }

        // ended my current one
        if (right[current] == i) {
            // printf("current = %d, right[%d] = %d\n", current, current, right[current]);
            current = -1;
            blocks.push_back(accum);
            accum.clear();
        }
    }

    int tot = 0;
    for (vector<int> v: blocks) {
        tot += ans(v);
    }
    printf("%d\n", tot);
}