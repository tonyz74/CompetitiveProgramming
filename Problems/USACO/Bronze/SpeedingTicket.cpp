#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void setIO() {
    freopen("speeding.in", "r", stdin);
    freopen("speeding.out", "w", stdout);
}

int main(void) {
    setIO();
    int N, M; cin >> N >> M;

    vector<pair<int, int> > speeds(N + 1);
    for (int i = 1; i <= N; i++) cin >> speeds[i].first >> speeds[i].second;

    vector<pair<int, int> > bessie(M + 1);
    for (int i = 1; i <= M; i++) cin >> bessie[i].first >> bessie[i].second;

    int speeds_i = 1;
    int bessie_i = 1;

    int s_speed = 0, s_bessie = 0;
    int worst_infraction = 0;

    for (int mi = 1; mi <= 100; mi++) {
        if (s_speed >= speeds[speeds_i].first) { s_speed = 0; speeds_i++; }
        if (s_bessie >= bessie[bessie_i].first) { s_bessie = 0; bessie_i++; }

        int actual_speed = bessie[bessie_i].second;
        int speed_limit = speeds[speeds_i].second;
        worst_infraction = max(worst_infraction, actual_speed - speed_limit);

        s_speed++; s_bessie++;
    }

    cout << worst_infraction << endl;
}