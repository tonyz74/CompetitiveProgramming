#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <assert.h>

using namespace std;

int n, k;
map<int, int> m;
vector<pair<int, int> > v;
vector<int> out;

bool check(int copies) {
    out.clear();
    int used = 0;
    int i = 0;

    while (i != (int) v.size()) {
        int rem = v[i].first;
        while (rem - copies >= 0) {
            rem -= copies;
            used++;
            out.push_back(v[i].second);

            if (used >= k) return true;
        }

        i++;
    }

    return used >= k;
}

int main(void) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        m[x]++; 
    }
    for (auto p = m.rbegin(); p != m.rend(); p++) {
        v.push_back(make_pair(p->second, p->first));
    }

    std::sort(v.begin(), v.end());

    int lo = 1, hi = 1e9;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    check(lo);

    std::sort(out.begin(), out.end());
    for (int i = 0; i < (int) out.size(); i++) {
        cout << out[i] << " ";
    }
}