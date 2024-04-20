#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

void solve(void) {
    int n; cin >> n;

    if (n == 1) {
        printf("1 1\n1 1 1\n");
        return;
    }

    vector<pair<int, int> > moves;

    vector<vector<int> > state(n + 1, vector<int>(n + 1, 0));

    for (int span = n; span >= 2; span--) {
        // first do rows
        for (int i = 1; i <= span; i++) {
            moves.push_back(make_pair(1, i));
            // for (int x = 1; x <= n; x++) {
            //     state[i][x] = x;
            // }
        }
        // then columns
        for (int j = 1; j <= span - 1; j++) {
            moves.push_back(make_pair(2, j));
            // for (int x = 1; x <= n; x++) {
            //     state[x][j] = x;
            // }
        }
    }


    int len = (int) moves.size();
    vector<vector<bool> > seen(3, vector<bool>(n + 1, false));

    vector<pair<int, int> > res_moves;
    for (int i = len - 1; i >= 0; i--) {
        auto p = moves[i];
        if (!seen[p.first][p.second]) {
            seen[p.first][p.second] = true;
            res_moves.push_back(p);
        }
    }

    std::reverse(res_moves.begin(), res_moves.end());
    
    int ans = 0;
    for (auto mov: res_moves) {
        if (mov.first == 1) {
            for (int x = 1; x <= n; x++) {
                state[mov.second][x] = x;
            }
        } else {
            for (int x = 1; x <= n; x++) {
                state[x][mov.second] = x;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans += state[i][j];
            // printf("%lld ", state[i][j]);
        }
        // printf("\n");
    }

    printf("%lld %lld\n", ans, (int) res_moves.size());
    for (auto mov: res_moves) {
        printf("%lld %lld ", mov.first, mov.second);
        for (int i = 1; i <= n; i++) {
            printf("%lld ", i);
        }
        printf("\n");
    }
}

signed main(void) {
    int t; cin >> t;
    while (t--) solve();
}