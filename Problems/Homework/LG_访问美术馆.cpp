#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

#define MAX_N (3 * 100 + 50)
#define MAX_PAINTINGS (2000 + 5)
#define SECS_PER_PAINTING 5
#define INVALID 1e5

using i64 = long long;

struct edge {
    i64 node;
    i64 wt;

    edge(i64 n, i64 w): node(n), wt(w) {
    }
};

i64 T, N;
vector<edge> children[MAX_N];
// stores the max paintings that can be taken from a given node (and subtree)
i64 value[MAX_N];

// dp[i][n] means currently at subtree rooted at i,
// min cost to take n paintings
i64 dp[MAX_N][MAX_PAINTINGS];

void solve(i64 node) {
    for (edge child: children[node]) solve(child.node);

    // currently a leaf
    if (children[node].size() == 0) {
        for (i64 i = 0; i <= value[node]; i++) {
            dp[node][i] = i * SECS_PER_PAINTING;
        }
    }

    // just carry over everything from the next one
    else if (children[node].size() == 1) {
        edge child = children[node][0];
        for (i64 take = 0; take <= value[child.node]; take++) {
            dp[node][take] = dp[child.node][take] + 2 * child.wt;
        }
        value[node] = value[child.node];
    }

    // fork of a binary tree
    else if (children[node].size() == 2) {
        edge left = children[node][0];
        edge right = children[node][1];

        for (i64 take_left = 0; take_left <= value[left.node]; take_left++) {
            i64 trav_left = min(take_left, 1ll) * 2 * left.wt;
            for (i64 take_right = 0; take_right <= value[right.node]; take_right++) {
                i64 trav_right = min(take_right, 1ll) * 2 * right.wt;
                i64 total_take = take_left + take_right;

                dp[node][total_take] = min(
                    dp[node][total_take], 
                    trav_left + trav_right + dp[left.node][take_left] + dp[right.node][take_right]
                );
            }
        }
        value[node] = value[left.node] + value[right.node];
    }

    // not 0, 1, or 2. generated the tree wrong. 
    else {
        assert(false);
    }

}

int main(void) {
    cin >> T;

    // create the tree
    {
        vector<pair<int, int> > input;
        i64 first;
        while (cin >> first) {
            i64 second; cin >> second;
            input.push_back(make_pair(first, second));
        }

        N = 1;
        i64 i = 0;

        children[1].push_back(edge(2, input[0].first));
        N++;
        if (input[0].second == 0) {
            i = 1;
            pair<int, int> curr = make_pair(2, 2);
            deque<pair<int, int> > stk;

            while (i != (int) input.size()) {
                curr.second--;
                N++;
                children[curr.first].push_back(edge(N, input[i].first));

                if (input[i].second == 0) {
                    stk.push_back(curr);
                    curr = make_pair(N, 2);
                } else {
                    value[N] = input[i].second;
                    while (curr.second == 0 && !stk.empty()) {
                        curr = stk.back();
                        stk.pop_back();
                    }
                }

                i++;
            }

        } else {
            value[2] = input[0].second;
        }
    }

    for (i64 i = 0; i < MAX_N; i++) {
        for (i64 j = 0; j < MAX_PAINTINGS; j++) {
            dp[i][j] = INVALID;
        }
    }

    solve(1);

    i64 ans = 0;
    for (i64 j = 1; j <= value[1]; j++) {
        if (dp[1][j] < T) {
            ans = max(ans, j);
        }
    }

    printf("%lld\n", ans);
}