#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void solve() {
    int n; cin >> n;
    set<int> a;
    map<int, int> events;

    for (int i = 1; i <= n; i++) {
        int A; cin >> A;
        a.insert(A);
    }

    for (auto x: a) {
        events[x + 1] += 1;
        events[x + n + 1] -= 1;
    }

    int ans = 0;
    int track = 0;
    for (auto e: events) {
        track += e.second;
        ans = max(track, ans);
    }

    printf("%d\n", ans);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();        
}