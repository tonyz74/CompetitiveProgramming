#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int N, D, M;
deque<pair<int, int> > rq_base;

bool check(int n_machines, bool show) {
    int available = n_machines;
    deque<int> current;
    deque<pair<int, int> > pending;
    deque<pair<int, int> > rq = rq_base;

    for (int day = 1; day <= N; day++) {
        while (!current.empty() && current.front() <= day) {
            available++;
            current.pop_front();
        }

        while (!rq.empty() && rq.front().first <= day) {
            auto f = rq.front();
            pending.push_back(make_pair(f.first + D, f.second));
            rq.pop_front();
        }

        // pop the ones that have tightest requirements
        while (available != 0 && !pending.empty()) {
            int need = pending.begin()->first;
            if (need < day) {
                return false;
            }

            if (show) printf("%d ", pending.begin()->second);

            // will get this printer back the next day
            current.push_back(day + 1);
            pending.erase(pending.begin());
            available--;
        }

        if (show) printf("0\n");
    }

    return true;
}


void read_rq_base() {
    vector<int> sorter[(int) 1e6 + 1];

    for (int i = 1; i <= M; i++) {
        int d; cin >> d;
        sorter[d].push_back(i);
    }

    for (int d = 1; d <= 1e6; d++) {
        for (int id: sorter[d]) {
            rq_base.push_back(make_pair(d, id));
        }
    }
}

#include <algorithm>
int main(void) {
    cin >> N >> D >> M;
    // read_rq_base();
    for (int i = 1; i <= M; i++) {
        int d; cin >> d;
        rq_base.push_back(make_pair(d, i));
    }
    std::sort(rq_base.begin(), rq_base.end());

    int lo = 1, hi = 1e6;
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (check(mid, 0)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d\n", lo);
    check(lo, 1);
}