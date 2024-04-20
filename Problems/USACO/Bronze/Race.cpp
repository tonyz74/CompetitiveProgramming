#include <iostream>
#include <vector>
#include <cmath>
#include <ctgmath>

typedef long long ll;

using namespace std;

ll K;

ll add_all(ll end) {
    if (end <= 0) return 0;
    return ((end) * (end + 1)) / 2;
}

ll add_in_range(ll start, ll end) {
    if (start > end) return 0;
    else if (start == end) return start;

    return add_all(end) - add_all(start - 1);
}

bool can_decelerate(ll dist_left, ll X, ll S) {
    if (S <= X) return true;

    // it takes curr_speed - X changes to decelerate to X 
    // to decelerate, we need to add:
    // (S - 1) + (S - 2) + (S - 3) + ... + (X + 1)
    ll need = add_in_range(X + 1, S - 1) + 1;
    return need <= dist_left;
}

void solve() {
    ll X; cin >> X;

    ll time = 0;
    ll speed = 0;
    ll dist_left = K;

    while (dist_left > 0) {
        // printf("[%lld]: ", time);
        if (can_decelerate(dist_left - (speed + 1), X, speed + 1)) {
            speed++;
        } else if (can_decelerate(dist_left - speed, X, speed)) {
            // no change
        } else {
            speed--;
        }

        dist_left -= speed;
        // printf("%lld, dist left now %lld\n", speed, dist_left);
        time++;
    }

    cout << time << endl;
}

int main(void) {
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);

    cin >> K;
    int N; cin >> N;
    for (int i = 0; i < N; i++) solve();
}