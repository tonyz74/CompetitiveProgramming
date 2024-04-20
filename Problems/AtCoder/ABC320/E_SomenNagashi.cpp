#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

enum event_type {
    REJOIN_QUEUE = 1,
    NOODLE_SUPPLY = 2
};

using x = pair<long long, long long>;

using p = pair<x, long long>;

int main(void) {
    long long N, M;
    cin >> N >> M;

    vector<long long> T(M + 1);
    vector<long long> W(M + 1);
    vector<long long> S(M + 1);

    vector<long long> noodles(N + 1, 0);
    priority_queue<p, vector<p>, greater<p> > next_events;
    priority_queue<long long, vector<long long>, greater<long long> > line;

    for (long long i = 1; i <= N; i++) {
        line.push(i);
    }

    for (long long i = 1; i < M + 1; i++) {
        cin >> T[i] >> W[i] >> S[i];
        next_events.push(make_pair(make_pair(T[i], NOODLE_SUPPLY), i));
    }

    while (!next_events.empty()) {
        // structure: time they return, person ID
        pair<pair<long long, long long>, long long> latest = next_events.top();
        next_events.pop();
        long long id = latest.second;
        long long time = latest.first.first;
        long long ev_type = latest.first.second;

        if (ev_type == NOODLE_SUPPLY) {

            // give it to the frontmost person
            if (!line.empty()) {
                long long frontmost = line.top();
                noodles[frontmost] += W[id];
                line.pop();

                next_events.push(make_pair(
                    make_pair(time + S[id], REJOIN_QUEUE),
                    frontmost
                ));
            }

        } else if (ev_type == REJOIN_QUEUE) {
            line.push(id);
        }
    }

    for (long long i = 1; i <= N; i++) {
        printf("%lld\n", noodles[i]);
    }
}