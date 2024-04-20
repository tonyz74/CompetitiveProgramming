#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main(void) {
    // 840 is the LCM of all possible P's,
    // so mod 840 will be a perfect cycle again, we will always
    // be able to wrap around at that point.
    //
    // so get closest mult to 840, then add that to the time taken
    // to ride the bus and walk (times[start % 840])

    ll times[841] = {0};

    ll N;
    cin >> N;

    ll X, Y;
    cin >> X >> Y;

    vector<ll> P(N, 0);
    vector<ll> T(N, 0);
    for (int i = 1; i < N; i++) {
        cin >> P[i];
        cin >> T[i];
    }

    for (ll st = 1; st <= 840; st++) {
        ll time = X + st;

        // now at station 1
        for (ll bus = 1; bus < N; bus++) {
            if (time % P[bus] != 0) {
                // make a multiple
                time += (P[bus] - time % P[bus]);
            }

            time += T[bus];
        }

        time += Y;
        times[st] = time;
    }

    times[0] = times[840] - 840;

    ll Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        ll q;
        cin >> q;

        ll nearest_mult = q / 840;

        cout << (nearest_mult * 840 + times[q % 840]) << endl;
    }
}