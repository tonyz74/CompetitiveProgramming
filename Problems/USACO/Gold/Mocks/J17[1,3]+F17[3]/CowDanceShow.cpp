#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

int N, T_max;
vector<int> d;
using p = pair<int, int>;

bool check(int K) {
    int time_now = 0;
    int i = 1;
    set<p> exit_times;
    set<int> dancing_cows;

    while (i <= K) {
        // printf("cow %d enters, will exit at %d\n", i, time_now + d[i]);
        dancing_cows.insert(i);
        exit_times.insert(make_pair(time_now + d[i], i));
        i++;
    }

    while (!exit_times.empty()) {
        auto front = *exit_times.begin();
        time_now = front.first;
        int exiter = front.second;
        // printf("cow %d leaves at time %d\n", exiter, time_now);

        exit_times.erase(*exit_times.begin());
        dancing_cows.erase(exiter);

        // printf("i = %d, size = %d, dancing cows: ", i, (int) dancing_cows.size());
        // for (int x: dancing_cows) {
            // printf("%d ", x);
        // }
        // printf("\n");
        if ((int) dancing_cows.size() < K && i <= N) {
            // printf("new cow %d joins (time is %d), will leave at %d\n", i, time_now, time_now + d[i]);
            dancing_cows.insert(i);
            exit_times.insert(make_pair(time_now + d[i], i));
            i++;
        }
    }

    return time_now <= T_max;
}

int main(void) {
    freopen("cowdance.in", "r", stdin);
    freopen("cowdance.out", "w", stdout);

    cin >> N >> T_max;
    d.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> d[i];
    }

    // printf("%d\n", check(1));
    // return 0;

    int lo = 1;
    int hi = N;

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d\n", lo);
}