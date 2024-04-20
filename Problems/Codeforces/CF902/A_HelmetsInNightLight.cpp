#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;
using i64 = long long;

void solve() {
    i64 n, p; cin >> n >> p;
    vector<i64> num_shares(n + 1);
    vector<i64> cost(n + 1);
    for (i64 i = 1; i <= n; i++) cin >> num_shares[i];
    for (i64 i = 1; i <= n; i++) cin >> cost[i];

    // the remaining opportunities for something of that cost
    map<i64, i64> rem;
    rem[p] = 1e9;

    multiset<pair<i64, i64> > unused;
    for (i64 i = 1; i <= n; i++) {
        unused.insert(make_pair(cost[i], num_shares[i]));
    }

    i64 total_cost = 0;
    while (!unused.empty()) {
        pair<i64, i64> best_receiver = *unused.begin();
        total_cost += rem.begin()->first;

        rem.begin()->second--;
        if (rem.begin()->second == 0) {
            rem.erase(rem.begin());
        }

        rem[best_receiver.first] += best_receiver.second;
        unused.erase(unused.find(best_receiver));
    }

    cout << total_cost << endl;
}

int main(void) {
    i64 t; cin >> t;
    while (t--) solve(); 
}