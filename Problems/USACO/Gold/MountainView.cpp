#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using i64 = long long;

using namespace std;

bool by_height(const pair<i64, i64>& lhs, const pair<i64, i64>& rhs) {
    // tallest ones go first, otherwise ones at the same starting position will
    // be counted multiple times, even though only the tallest should work
    return make_pair(lhs.second, lhs.first) > make_pair(rhs.second, rhs.first);
}

int main(void) {
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);

    i64 N;
    cin >> N;

    vector<pair<i64, i64> > peaks(N);
    for (i64 i = 0; i < N; i++) cin >> peaks[i].first >> peaks[i].second;
    std::sort(peaks.begin(), peaks.end(), by_height);

    vector<pair<i64, i64> > x_coords;

    i64 counter = 1;
    for (auto && [x1, y1]: peaks) {
        // y - y1 = x - x1
        // 0 - y1 = x - x1
        // x = x1 - y1

        // y - y1 = -(x - x1)
        // x = x1 + y1

        x_coords.push_back({x1 - y1, counter});
        x_coords.push_back({x1 + y1, counter});

        counter++;
    }
    std::sort(x_coords.begin(), x_coords.end());

    map<i64, pair<i64, i64> > indices;
    for (i64 i = 0; i < (i64) x_coords.size(); i++) {
        i64 counter = x_coords[i].second; 

        if (indices.count(counter) == 0) {
            indices[counter].first = i;
        } else {
            indices[counter].second = i;
        }
    }


    // a mountain is actually only obscured by another when its base is
    // entirely within the other mountain's base. we can keep track of running max.

    // we don't have to consider min because we're going in sorted order anyways,
    // so the region between the LEFTMOST mountain and the RIGHTMOST ACTIVE MOUNTAIN
    // is always our region for elimination.

    i64 vis = 0;
    i64 max_right = 0;

    for (i64 i = 0; i < (i64) x_coords.size(); i++) {
        i64 my_id = x_coords[i].second;

        if (i == indices[my_id].first) {
            if (x_coords[indices[my_id].second].first > max_right) {
                max_right = x_coords[indices[my_id].second].first;
                vis++;
            } 
        }
    }

    cout << vis << endl;
}