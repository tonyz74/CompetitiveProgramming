#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

using i64 = long long;

enum event_type {
    ARRIVE,
    FINISH_EATING
};

struct cow {
    i64 id;
    i64 arrival;
    i64 delay;

    bool operator<(const cow& rhs) const {
        // small seniorities are more important
        return id < rhs.id;
    }
};

struct event {
    i64 time;
    event_type ty;
    int cow_id;

    bool operator<(const event& rhs) const {
        // whoever has the smallest time wins
        // arriving comes before finishing eating
        // large seniorities should have higher priority
        return make_tuple(time, (i64) ty, cow_id) < make_tuple(rhs.time, (i64) rhs.ty, rhs.cow_id);
    }
};

int main(void) {
    freopen("convention2.in", "r", stdin);
    freopen("convention2.out", "w", stdout);

    int N; cin >> N;

    set<event> events;
    set<cow> waiting;

    vector<cow> cows(N);
    for (int i = 0; i < N; i++) {
        cin >> cows[i].arrival >> cows[i].delay;
        cows[i].id = i;
    }

    for (int i = 0; i < N; i++) {
        event e;
        e.time = cows[i].arrival;
        e.ty = ARRIVE;
        e.cow_id = i;
        events.insert(e);
    }

    vector<i64> start_times(N + 1, -1);
    i64 time_now = events.begin()->time;

    // printf("start: %d\n", (int) events.size());
    
    bool has_current = false;

    while (!events.empty()) {
        event latest = *events.begin();
        events.erase(events.begin());

        // printf("n events is now %d\n", (int) events.size());

        time_now = latest.time;

        // printf("at time %lld, got event:\n", time_now);
        // if (latest.ty == FINISH_EATING) {
        //     printf("    [Finished Eating] (cow %d)\n", latest.cow_id + 1);
        // } else {
        //     printf("    [Arrived] (cow %d)\n", latest.cow_id + 1);
        // }

        if (latest.ty == FINISH_EATING) {
            has_current = false;
        } else if (latest.ty == ARRIVE) {
            waiting.insert(cows[latest.cow_id]);
        }

        if (!waiting.empty() && !has_current) {
            cow head = *waiting.begin();
            waiting.erase(waiting.begin());

            start_times[head.id] = time_now;

            // printf("   - cow %lld is now eating\n", head.id + 1);

            event e;
            e.time = time_now + cows[head.id].delay;
            e.ty = FINISH_EATING;
            e.cow_id = head.id;

            events.insert(e);
            
            has_current = true;
        }
    }

    i64 max_diff = 0;
    for (int i = 0; i < N; i++) {
        max_diff = max(max_diff, start_times[i] - cows[i].arrival);
    }
    cout << max_diff << endl;
}