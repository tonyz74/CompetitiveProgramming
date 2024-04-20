#include <iostream>
#include <vector>

using namespace std;

#define MAX_N ((long long)(1e6 + 5))

typedef long long ll;

struct req {
    int start, end;
    int rooms;
};

int N, M;
vector<int> R;
vector<req> Q;

// judge whether the requests between 0 and `end` have no conflict
bool no_conflict(int end) {
    if (end == 0) return true;

    ll events[MAX_N] = {0};

    for (int i = 1; i <= end; i++) {
        events[Q[i].start] += Q[i].rooms;
        events[Q[i].end + 1] -= Q[i].rooms;
    }

    ll curr = 0;
    for (int i = 1; i <= N; i++) {
        curr += events[i];
        if (curr > R[i]) return false;
    }

    return true;
}

int main(void) {
    cin >> N >> M;
    R.resize(N + 1);
    for (int i = 1; i <= N; i++) cin >> R[i];

    Q.resize(M + 1);
    for (int i = 1; i <= M; i++) {
        cin >> Q[i].rooms >> Q[i].start >> Q[i].end;
    }

    int lo = 0;
    int hi = M;

    // last_true functionality
    while (lo < hi) {
        // round up?
        int mid = lo + (hi - lo + 1) / 2;
        // printf("mid is %d, lo is %d, hi is %d\n", mid, lo, hi);

        if (no_conflict(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    
    // printf("no_conflict: %d\n", no_conflict(3));

    if (lo == M) {
        printf("0\n");
    } else {
        printf("-1\n%d\n", lo + 1);
    }
}