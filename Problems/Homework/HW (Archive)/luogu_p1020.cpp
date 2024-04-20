#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

vector<int> heights;
vector<int> missiles;

int lds() {
    vector<int> cache;
    cache.push_back(-heights[0]);

    for (size_t i = 1; i < heights.size(); i++) {
        auto it = upper_bound(
            cache.begin(),
            cache.end(),
            -heights[i]
        );
        
        if (it == cache.end()) {
            cache.push_back(-heights[i]);
        } else {
            *it = -heights[i];
        }
    }

    return cache.size();
}

int main(void) {
    missiles.reserve(1000001);
    heights.reserve(1000001);

    int height = 0;

    while (scanf("%d", &height) != EOF) {
        heights.push_back(height);

        // find the turret that's closest and not less than or equal to
        // the current missile height.
        auto loc = lower_bound(missiles.begin(), missiles.end(), height);

        if (loc == missiles.end()) {
            missiles.push_back(height);
        } else {
            *loc = height;
        }
    }

    printf("%d\n", lds());
    printf("%lu\n", missiles.size());
}
