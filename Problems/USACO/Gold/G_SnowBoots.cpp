#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>

using namespace std;

using i64 = long long;

struct tile {
    i64 depth;
    int id;

    bool operator<(const tile& rhs) const {
        return depth < rhs.depth;
    }
};

struct boot {
    i64 depth;
    i64 dist;
    int id;

    bool operator<(const boot& rhs) const {
        return make_tuple(depth, dist, id) < make_tuple(rhs.depth, rhs.dist, rhs.id);
    }
};

i64 N, B;
multiset<tile> tiles;
set<i64> locations;

vector<boot> boots;

int main(void) {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);

    cin >> N >> B;

    for (i64 i = 0; i < N; i++) {
        tile t; cin >> t.depth;
        t.id = i;
        tiles.insert(t); 
        locations.insert(i);
    }

    i64 max_dist = 1;

    for (i64 i = 0; i < B; i++) {
        boot b;
        cin >> b.depth >> b.dist;
        b.id = i;
        boots.push_back(b);
    }
    std::sort(boots.begin(), boots.end());
    std::reverse(boots.begin(), boots.end());

    vector<bool> answers(B);
    for (i64 b = 0; b < B; b++) {
        // first greater than the max capacity of this boot.
        // remove all of them, updating max dist along the way
        tile seek;
        seek.depth = boots[b].depth;
        seek.id = -1;
        auto it = tiles.upper_bound(seek);

        // multiset iterators don't get invalidated
        while (it != tiles.end()) {
            i64 pos = it->id;

            auto loc = locations.lower_bound(pos);
            auto pre_it = loc; pre_it--;
            auto post_it = loc; post_it++;

            // 3 4 _ 6
            //    ^
            i64 diff = *post_it - *pre_it;
            max_dist = max(max_dist, diff);

            locations.erase(loc);

            auto next = it;
            next++;
            tiles.erase(it);
            it = next;
        }

        answers[boots[b].id] = boots[b].dist >= max_dist;
    }

    for (i64 i = 0; i < B; i++) {
        cout << answers[i] << endl;
    }
}