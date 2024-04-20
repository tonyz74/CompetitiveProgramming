#include <iostream>
#include <set>
#include <vector>


// set is faster than unordered set somehow
// i do not understand this but sure

using namespace std;

int main(void) {
    int N, Q; cin >> N >> Q;

    vector<set<int> > v;
    v.resize(N);

    for (int i = 0; i < N; i++) {
        int c; cin >> c;
        v[i].insert(c);
    }

    for (int q = 0; q < Q; q++) {
        int a, b; cin >> a >> b;
        // we're using 0 based
        a--; b--;

        if (v[a].size() > v[b].size()) {
            for (int c: v[b]) v[a].insert(c);
            v[b].clear();
            swap(v[a], v[b]);
        } else {
            for (int c: v[a]) v[b].insert(c);
            v[a].clear();
        }

        printf("%lu\n", v[b].size());
    }
}