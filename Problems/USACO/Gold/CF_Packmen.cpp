#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N;
string game;
vector<int> stars;
vector<int> packmen;

bool can_eat(int time) {
    int n_stars = stars.size();
    int n_packmen = packmen.size();
    // eat everything to the left

    // packmen + stars => still O(N)
    int i = 0;

    for (int pac = 0; pac < n_packmen; pac++) {
        if (i == n_stars) {
            continue;
        }

        int leftmost = stars[i];
        int mandatory_left_dist = max(packmen[pac] - leftmost, 0);

        // would never even reach the left side
        if (mandatory_left_dist > time) {
            return false;
        }

        // try going left, normal, right
        int left_first_dist = packmen[pac] + time - 2 * mandatory_left_dist;
        // try going right, normal, left
        int right_first_dist = packmen[pac] + (time - mandatory_left_dist) / 2;

        int best_right = max(left_first_dist, right_first_dist);

        for (; i < n_stars; i++) {
            if (stars[i] > best_right) break;
        }
    }

    return (i == n_stars);
}

int main(void) {
    cin >> N;
    cin >> game;

    int i = 0;
    for (char c: game) {
        if (c == 'P') packmen.push_back(i);
        else if (c == '*') stars.push_back(i);
        i++;
    }

    std::sort(packmen.begin(), packmen.end());
    std::sort(stars.begin(), stars.end());

    int lo = 1;
    int hi = 2 * 1e5 + 2;

    // find first true
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (can_eat(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d\n", lo);
}