#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int N, Q;
set<int> orig;
vector<pair<int, int> > X;
map<int, int> to_compressed;

int first_lteq(int v) {
    auto lb = orig.lower_bound(v);
    // nobody greater than or equal to
    if (lb == orig.end()) {
        lb--;
        return *lb;
    }

    if (*lb == v) return v;
    else if (lb == orig.begin()) {
        // greater and equal, yet it's the start: everybody's gteq
        return -1;
    } else {
        lb--;
        return *lb;
    }
}

int first_gteq(int v) {
    auto lb = orig.lower_bound(v);
    // nobody greater than or equal to
    if (lb == orig.end()) {
        return -1;
    }
    return *lb;
}

int main(void) {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);

    cin >> N >> Q;
    X.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> X[i].first;
        X[i].second = i;
        orig.insert(X[i].first);
    }

    std::sort(X.begin() + 1, X.end()); 
    for (int i = 1; i <= N; i++) {
        to_compressed[X[i].first] = i;
    }

    for (int i = 1; i <= Q; i++) {
        int a, b; cin >> a >> b;
        if (a > b) std::swap(a, b);
        int left = first_gteq(a);
        int right = first_lteq(b);

        // printf("%d %d => %d, %d:    ", a, b, left, right);
        if (left == -1 && right == -1) {
            assert(false);
        }

        if (left > right || left == -1 || right == -1) {
            printf("0\n");
        } else {
            int match_a = to_compressed[left];
            int match_b = to_compressed[right];

            printf("%d\n", match_b - match_a + 1);
        }

    }

}