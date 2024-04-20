#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, t; cin >> n >> t;

    // everything adjacent to some node u
    vector<vector<pair<int, int> > > adj(n + 1);

    for (int i = 1; i <= t; i++) {
        int m; cin >> m;
        for (int j = 1; j <= m; j++) {
            int x, y; cin >> x >> y;
            adj[x].emplace_back(y, i);
            adj[y].emplace_back(x, i);
        }
    }

    int k; cin >> k;
    vector<vector<int> > reach(t + 1);

    for (int i = 1; i <= k; i++) {
        int a; cin >> a;
        reach[a].emplace_back(i);
    }

    // smallest to come first, so greater<> to compare
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
    pq.emplace(0, 1);

    vector<int> dp(n + 1, 1e9);
    dp[1] = 0;

    vector<bool> seen(n + 1, false);

    while (!pq.empty()) {
        // first => time to reach here
        // second => the city reached

        pair<int, int> top = pq.top();
        pq.pop();

        if (seen[top.second]) continue;
        seen[top.second] = true;

        // printf("\n\nconsidering %d %d\n", top.first, top.second);

        for (auto conn: adj[top.second]) {
            int dst = conn.first;
            int x = conn.second;        // which snapshot must we be in?

            // printf("  trying to go to %d, %d\n", dst, x);

            auto next = lower_bound(reach[x].begin(), reach[x].end(), top.first + 1);

            // if (next != reach[x].end()) {
            //     printf("    min time was %d\n", *next);
            // }

            if (next != reach[x].end() && *next < dp[dst]) {
                dp[dst] = *next;
                pq.emplace(*next, dst);
            }
        }
    }

    if (dp[n] == 1e9) cout << -1 << endl;
    else cout << dp[n] << endl;
}