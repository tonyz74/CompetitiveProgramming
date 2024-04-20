#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct flight {
    int c, d, r, s;

    bool operator<(const flight& rhs) const {
        return (r < rhs.r);
    }
};

vector<int> layovers;
vector<int> min_time;
vector<vector<flight> > outgoing;

vector<flight> info;

void search(int airport) {
    auto& leave = outgoing[airport];

    int min_leave = min_time[airport] + layovers[airport];
    if (airport == 1) min_leave = min_time[airport];

    // printf("max leave at %d = %d\n", airport, min_leave);

    vector<flight> can_take;
    while (!leave.empty() && leave.back().r >= min_leave) {
        can_take.push_back(leave.back());
        leave.pop_back();
    }

    for (flight f: can_take) {
        min_time[f.d] = min(min_time[f.d], f.s);
        search(f.d);
    }
}

int main(void) {
    int N, M; cin >> N >> M;

    layovers.resize(N + 1);
    info.resize(M + 1);
    outgoing.resize(N + 1);

    for (int i = 1; i <= M; i++) {
        cin >> info[i].c >> info[i].r >> info[i].d >> info[i].s;
        outgoing[info[i].c].push_back(info[i]);
    }

    for (int i = 1; i <= N; i++) {
        sort(outgoing[i].begin(), outgoing[i].end());
    }

    for (int i = 1; i <= N; i++) {
        cin >> layovers[i];
    }

    min_time.resize(N + 1, 1e9);
    min_time[1] = 0;

    search(1);
    for (int i = 1; i <= N; i++) {
        if (min_time[i] == 1e9) {
            cout << -1 << endl;
        } else {
            cout << min_time[i] << endl;
        }
    }
}