#include <iostream>
#include <vector>

using namespace std;

struct union_find {
    vector<int> parents;

    union_find(int cap) {
        parents.resize(cap, 0);
        for (int i = 0; i < cap; i++) {
            parents[i] = i;
        }
    }

    int find(int x) {
        if (parents[x] == x) {
            return x;
        }

        int parent = find(parents[x]);
        parents[x] = parent;

        return parent;
    }

    void combine(int a, int b) {
        parents[find(b)] = find(a);
    }
};

typedef long long ll;

struct point { ll x, y, z; };

ll distance(point a, point b) {
    ll diff1 = (a.x - b.x);
    ll diff2 = (a.y - b.y);
    ll diff3 = (a.z - b.z);

    return diff1*diff1 + diff2*diff2 + diff3*diff3;
}

bool has_intersection(point a, point b, ll rad) {
    return distance(a, b) <= (4 * rad * rad);
}

void solve(void) {
    int n, h, r;
    cin >> n >> h >> r;

    // assume index n -> floor, index n + 1 -> ceiling
    union_find ds(n + 2);
    vector<point> known_points;

    int BOTTOM = n;
    int TOP = n + 1;

    for (int i = 0; i < n; i++) {
        point hole;
        cin >> hole.x >> hole.y >> hole.z;

        if (hole.z - r <= 0) {
            ds.combine(i, BOTTOM);
        }

        if (hole.z + r >= h) {
            ds.combine(i, TOP);
        }

        for (int j = 0; j < known_points.size(); j++) {
            if (has_intersection(known_points[j], hole, r)) {
                ds.combine(i, j);
            }
        }

        known_points.push_back(hole);
    }

    if (ds.find(BOTTOM) == ds.find(TOP)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}

int main(void) {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) solve();
}