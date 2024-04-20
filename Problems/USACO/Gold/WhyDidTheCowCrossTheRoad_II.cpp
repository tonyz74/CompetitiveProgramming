#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

int main(void) {
    freopen("maxcross.in", "r", stdin);
    freopen("maxcross.out", "w", stdout);

    i64 N, K, B; cin >> N >> K >> B;
    
    vector<bool> is_broken(N + 1);
    for (i64 i = 0; i < B; i++) {
        i64 broken_pos; cin >> broken_pos;
        is_broken[broken_pos] = true;
    }

    vector<i64> presum(N + 1);
    for (i64 i = 1; i <= N; i++) {
        presum[i] = presum[i - 1] + (int) (is_broken[i]);
    }

    i64 min_cost = 1e9;

    // getting only K continuous is optimal; if there are more to the
    // right, sliding over would be the best move and we'll include
    // that later, so we just need to have one length
    for (i64 i = 0; i + K <= N; i++) {
        i64 n_broken = presum[i + K] - presum[i];
        min_cost = min(min_cost, n_broken);
    }

    cout << min_cost << endl;
}