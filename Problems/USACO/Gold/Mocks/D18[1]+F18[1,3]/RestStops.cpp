#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
using i64 = long long;

int main(void) {
    freopen("reststops.in", "r", stdin);
    freopen("reststops.out", "w", stdout);

    i64 L, N, RF, RB; cin >> L >> N >> RF >> RB;

    map<i64, i64> pos_to_rest_i;
    vector<pair<i64, i64> > sfx_max(N + 2);
    vector<pair<i64, i64> > rest_stops(N + 1);

    for (i64 i = 1; i <= N; i++) {
        cin >> rest_stops[i].first >> rest_stops[i].second;
        pos_to_rest_i[rest_stops[i].first] = i;
    }

    for (i64 i = N; i >= 1; i--) {
        sfx_max[i] = sfx_max[i + 1];
        if (rest_stops[i].second > sfx_max[i].second) {
            sfx_max[i] = rest_stops[i];
        }
    }

    // bessie will go to the first maximum, rest as much as possible,
    // waiting for FJ to catch up, then go to the next best place, and so on
    i64 target_i = 1;

    i64 time = 0;
    i64 tastiness = 0;
    i64 bessie_pos = 0;

    while (target_i != N + 1) {
        i64 target_pos = sfx_max[target_i].first;
        target_i = pos_to_rest_i[target_pos];

        i64 diff = target_pos - bessie_pos;
        bessie_pos = target_pos;
        time += diff * RB;

        // how many seconds will it take for FJ to arrive at bessie's pos?
        i64 FJ_walk_time = bessie_pos * RF;

        // printf("bessie now at %lld at time %lld\n", bessie_pos, time);
        // printf("takes FJ %lld seconds total to get here\n", FJ_walk_time);

        // as soon as FJ arrives, bessie must leave
        // printf("bessie eats for %lld seconds, gaining time * %lld\n", FJ_walk_time - time, sfx_max[target_i].second);
        tastiness += (FJ_walk_time - time) * sfx_max[target_i].second;
        time = FJ_walk_time;
        // printf("FJ arrives at time %lld\n\n", FJ_walk_time);

        target_i++;
    }

    printf("%lld\n", tastiness);
}