#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> missiles;


int main(void) {
    missiles.reserve(1000001);

    int height = 0;

    while (scanf("%d", &height) != EOF) {
        // find the turret that's closest and not less than or equal to
        // the current missile height.
        auto loc = lower_bound(missiles.begin(), missiles.end(), height);

        if (loc == missiles.end()) {
            missiles.push_back(height);
        } else {
            *loc = height;
        }
    }

    printf("%lu\n", missiles.size());
}
