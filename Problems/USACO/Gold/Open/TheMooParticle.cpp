#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <set>

using namespace std;

void setIO() {
#ifndef TZ74_LOCAL_TESTING
    freopen("moop.in", "r", stdin);
    freopen("moop.out", "w", stdout);
#endif
}

struct coord {
    int x = -2e9, y = -2e9;
    int id = 0;

    coord() {}
    coord(int x, int y, int id) {
        this->x = x;
        this->y = y;
        this->id = id;
    }

    bool operator<(const coord& rhs) const {
        return make_pair(y, x) < make_pair(rhs.y, rhs.x);
    }
};

bool cmp_by_x(coord a, coord b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}

int main(void) {
    setIO();

    int N; cin >> N;
    vector<coord> coords(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> coords[i].x >> coords[i].y;
        coords[i].id = i;
    }

    std::sort(coords.begin() + 1, coords.end(), cmp_by_x);

    // for (int i = 1; i <= N; i++) {
    //     printf("%d %d\n", coords[i].x, coords[i].y);
    // }
    
    set<coord> future_y;
    for (int i = 1; i <= N; i++) {
        future_y.insert(coords[i]);
    }

    int group_id = 0;
    map<int, set<coord> > members;
    vector<int> group_of(N + 1, 0);

    // printf("\n");
    for (int i = 1; i <= N; i++) {
        // must make a new group
        if (members[group_id].size() == 0) {
            // printf("id was %d, updating\n", group_id);
            ++group_id;
            group_of[i] = group_id;
        }

        // lowest one in the group i'm joining
        int max_y = (members[group_id].size() == 0) ? (1e9 + 4) : members[group_id].begin()->y;

        // find any x that has y less than prev, and greater than me
        auto me = future_y.find(coords[i]);
        while (me->y <= max_y && me != future_y.end()) {
            // printf("me %d %d\n", me->x, me->y);
            group_of[me->id] = group_id;
            members[group_id].insert(*me);
            me++;
        }

        future_y.erase(coords[i]);
        members[group_id].erase(coords[i]);
    }

    cout << group_id << endl;
}