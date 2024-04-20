#include <vector>
#include <algorithm>

using namespace std;

using p = pair<int, int>;

bool cmp(const p& lhs, const p& rhs) {
    // return make_pair(lhs.first + lhs.second, lhs.first) < make_pair(rhs.first + rhs.second, rhs.first);
    return lhs.first + lhs.second < rhs.first + rhs.second;
}

int main(void) {
    vector<p> pairs = {
        {1, 2},
        {4, 9},
        {4, 8},
        {40, 12},
        {48, 1},
        {9, 7}
    };

    std::sort(pairs.begin(), pairs.end());

    for (int k = 1; k <= 10; k++) {
        for (auto p: pairs) {
            printf("%d [%d %d] ", p.second + k * p.first, p.first, p.second);
        }
        printf("\n");
    }
}