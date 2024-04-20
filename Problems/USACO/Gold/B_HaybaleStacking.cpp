#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

int main(void) {
    // freopen("stacking.in", "r", stdin);
    // freopen("stacking.out", "w", stdout);

    int N, K; cin >> N >> K;

    vector<i64> events(N + 2);
    vector<i64> final_state(N + 1, 0);

    for (int k = 0; k < K; k++) {
        i64 L, R;
        cin >> L >> R;

        events[L] += 1;
        events[R + 1] -= 1;
    }

    i64 weight = 0;
    for (i64 i = 1; i <= N; i++) {
        weight += events[i];
        final_state[i] = weight;
    }

    std::sort(final_state.begin() + 1, final_state.end());
    printf("%lld\n", final_state[N / 2 + 1]);
}