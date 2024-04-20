#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using i64 = long long;
using p = pair<i64, i64>;

int main(void) {
    i64 N; cin >> N;
    i64 M; cin >> M;

    std::priority_queue<p, vector<p>, less<p> > pq;
    vector<i64> S(N);
    for (i64 i = 0; i < N; i++) {
        cin >> S[i];
        pq.push(make_pair(S[i], i));
    }

    vector<bool> seen(N + 1);

    // i64 total_cost = 0;

    while (!pq.empty()) {
        p top = pq.top();
        pq.pop();

        if (seen[top.second]) continue;
        seen[top.second] = true;

        if (top.second != 0) {
            i64 lhs = S[top.second - 1];
            if (lhs < S[top.second] - M) {
                // total_cost += (S[top.second] - M) - lhs;
                S[top.second - 1] = S[top.second] - M;

                pq.push(make_pair(S[top.second - 1], top.second - 1));
            }
        }

        if (top.second != N - 1) {
            i64 rhs = S[top.second + 1];
            if (rhs < S[top.second] - M) {
                // total_cost += (S[top.second] - M) - rhs;
                S[top.second + 1] = S[top.second] - M;

                pq.push(make_pair(S[top.second + 1], top.second + 1));
            }
        }

    }

    // cout << total_cost << endl;
    for (i64 i = 0; i < N; i++) {
        cout << S[i] << " ";
    }
    cout << endl;

}