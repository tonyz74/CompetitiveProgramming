#include <iostream>
#include <vector>

using namespace std;

#define LEN ((int) 1e6)
int H, K;
vector<int> pos;

bool can_create(int max_dist) {
    // first enumerate which house to start from
}

int main(void) {
    cin >> H;
    pos.resize(H + 1);
    for (int i = 1; i <= H; i++) cin >> pos[i];
    std::sort(pos.begin() + 1, pos.end());
    cin >> K;

    int lo = 0;
    int hi = LEN;

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (can_create(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d\n", lo);
}