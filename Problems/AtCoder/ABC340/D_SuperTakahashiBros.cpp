#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using i64 = long long;
const i64 MAX_N = 2 * 1e5 + 4;

struct conn {
    i64 dst;
    i64 wt;

    conn() {}
    conn(i64 d, i64 w) : dst(d), wt(w) {}

    bool operator<(const conn& rhs) const {
        return make_pair(wt, dst) < make_pair(rhs.wt, rhs.dst);
    }
};

i64 N;
vector<conn> graph[MAX_N];

int main(void) {
    cin >> N;

    for (int i = 1; i <= N - 1; i++) {
        i64 A, B, X; cin >> A >> B >> X;
        graph[i].push_back(conn(X, B));
        graph[i].push_back(conn(i + 1, A));
    }

    priority_queue<conn> pq;
    vector<i64> shortest(MAX_N, 1e18);
    vector<bool> seen(MAX_N, 0);
    shortest[1] = 0;
    pq.push(conn(1, 0));

    while (!pq.empty()) {
        conn top = pq.top();
        pq.pop();
        if (seen[top.dst]) continue;
        seen[top.dst] = true;

        for (conn edge: graph[top.dst]) {
            i64 candidate = edge.wt + shortest[top.dst];
            if (candidate < shortest[edge.dst]) {
                shortest[edge.dst] = edge.wt + shortest[top.dst];
                // priority queue sorts by biggest first so we negate
                pq.push(conn(edge.dst, -shortest[edge.dst]));
            }
        }
    }

    printf("%lld\n", shortest[N]);
}