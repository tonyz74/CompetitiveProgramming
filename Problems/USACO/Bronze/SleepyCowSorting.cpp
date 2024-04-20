#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    freopen("sleepy.in", "r", stdin);
    freopen("sleepy.out", "w", stdout);

    int N; cin >> N;
    vector<int> P(N); for (int i = 0; i < N; i++) cin >> P[i];

    int ending_sorted = 1;
    for (int i = N - 2; i >= 0; i--) {
        if (P[i] < P[i + 1]) ending_sorted++;
        else break;
    }

    printf("%d\n", N - ending_sorted);
}