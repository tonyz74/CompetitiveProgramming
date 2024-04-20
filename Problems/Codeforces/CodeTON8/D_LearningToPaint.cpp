#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;
using i64 = long long;

void solve() {
    i64 N, K; cin >> N >> K;
    vector<vector<i64> > A(N + 1, vector<i64>(N + 1, 1e9));

    for (i64 i = 1; i <= N; i++) {
        for (i64 j = i; j <= N; j++) {
            cin >> A[i][j];
        }
    }

    vector<vector<i64> > dp(N + 1);
    vector<vector<i64> > prefix_best(N + 1);
    prefix_best[0] = vector<i64>{0};

    for (i64 i = 1; i <= N; i++) {
        vector<i64> best_now;

        // must be at least gap of 1, j + 2 is where i ends
        priority_queue<pair<i64, int> > choices;
        vector<int> taken(N + 1);
        for (i64 j = 0; j <= i - 2; j++) {
            taken[j] = 0;
            i64 val = A[j + 2][i] + prefix_best[j][taken[j]];
            choices.push(make_pair(val, j));
        }

        choices.push(make_pair(A[1][i], -1));

        for (i64 take = 1; take <= K; take++) {
            if (choices.empty()) {
                break;
            }

            // best choice
            auto cho = choices.top();
            choices.pop();
            best_now.push_back(cho.first);

            i64 j = cho.second;
            if (j == -1) continue;
            taken[j]++;
            if (taken[j] < (i64) prefix_best[j].size()) {
                i64 val = A[j + 2][i] + prefix_best[j][taken[j]];
                choices.push(make_pair(val, j));
            }
        }

        dp[i] = best_now;

        // now combine best_now and prefix_best[i - 1]
        vector<i64> pfx_now;
        i64 now_i = 0, pfx_i = 0;
        i64 sz_now = best_now.size(), sz_pfx = prefix_best[i - 1].size();

        for (i64 take = 1; take <= K; take++) {
            if (now_i == sz_now && pfx_i == sz_pfx) break;

            if (now_i == sz_now) {
                pfx_now.push_back(prefix_best[i - 1][pfx_i++]);
            } else if (pfx_i == sz_pfx) {
                pfx_now.push_back(best_now[now_i++]);
            } else if (best_now[now_i] >= prefix_best[i - 1][pfx_i]) {
                pfx_now.push_back(best_now[now_i++]);
            } else {
                pfx_now.push_back(prefix_best[i - 1][pfx_i++]);
            }
        }

        prefix_best[i] = pfx_now;
    }

    for (i64 x: prefix_best[N]) {
        printf("%lld ", x);
    }
    printf("\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}