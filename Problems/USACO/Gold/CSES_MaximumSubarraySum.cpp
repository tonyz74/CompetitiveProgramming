#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

int main(void) {
    int N; cin >> N;
    vector<i64> X(N + 1);

    for (int i = 1; i <= N; i++) cin >> X[i];

    vector<i64> pre(N + 1);
    i64 min_lead = 0;

    i64 best = -1e18;
    for (int i = 1; i <= N; i++) {
        pre[i] = pre[i - 1] + X[i];

        best = max(best, pre[i] - min_lead);
        min_lead = min(min_lead, pre[i]);
    }

    cout << best << endl;
}