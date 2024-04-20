#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define TYPE_PUSH 1
#define TYPE_POP 2

struct evt {
    int ty;
    int id;

    evt(int t, int i): ty(t), id(i) {}
};

int main(void) {
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    int N; cin >> N;
    map<int, vector<evt> > events;
    map<int, int> n_singles;
    map<int, int> n_singles_upon_entry;

    for (int i = 1; i <= N; i++) {
        int s, e; cin >> s >> e;
        // printf("#%d: %d %d\n", i, s, e);
        events[s].push_back(evt(TYPE_PUSH, i));
        events[e].push_back(evt(TYPE_POP, i));
    }

    int cnt = 0;
    int prev_time = 0;
    int one_accum = 0;
    int total_val = 0;

    for (auto p: events) {
        int time = p.first;
        const vector<evt>& v = p.second;

        // only one thing covering this region
        if (cnt == 1) {
            one_accum += time - prev_time;
        }
        if (cnt != 0) {
            total_val += time - prev_time;
        }

        for (evt e: v) {
            if (e.ty == TYPE_PUSH) {
                n_singles_upon_entry[e.id] = one_accum;
                cnt++;
            } else {
                n_singles[e.id] = one_accum - n_singles_upon_entry[e.id];
                cnt--;
            }
        }

        prev_time = time;
    }

    int mn_singles = 1e9 + 10;
    for (int i = 1; i <= N; i++) {
        mn_singles = min(mn_singles, n_singles[i]);
    }
    printf("%d\n", total_val - mn_singles);
    // printf("total covered: %d\n", total_val);
    // for (int i = 1; i <= N; i++) {
    //     printf("%d\n", n_singles[i]);
    // }
}