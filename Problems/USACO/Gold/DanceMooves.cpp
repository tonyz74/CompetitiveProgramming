#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const int MAX_N = 1e5 + 4;
const int MAX_K = 2e5 + 4;

int N, K;
pair<int, int> cmds[MAX_K];
vector<int> graph[MAX_N];

int group_id = 1;
int group_of[MAX_N];
set<int> dsts_by_group[MAX_N];

void dfs(int now) {
    if (group_of[now] != 0) return;
    group_of[now] = group_id;

    for (int conn: graph[now]) {
        if (group_of[conn] == 0) {
            dfs(conn);
        }
    }
}

int main(void) {
    cin >> N >> K;

    for (int i = 1; i <= K; i++) {
        cin >> cmds[i].first >> cmds[i].second;
    }

    // simulate once to find ending points (build graph and
    // find connected components).
    vector<int> state(N + 10);
    for (int i = 1; i <= N; i++) state[i] = i;
    for (int command = 1; command <= K; command++) {
        auto c = cmds[command];
        std::swap(state[c.first], state[c.second]);
    }

    for (int i = 1; i <= N; i++) {
        if (state[i] != i) {
            graph[i].push_back(state[i]);
            graph[state[i]].push_back(i);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (group_of[i] == 0) {
            dfs(i);
            group_id++;
        }
    }

    // now simulate once more, this iteration, add each destination
    // to a group so we can save on time.

    for (int i = 1; i <= N; i++) {
        state[i] = i;
        dsts_by_group[group_of[state[i]]].insert(i);
    }

    for (int command = 1; command <= K; command++) {
        auto c = cmds[command];
        dsts_by_group[group_of[state[c.first]]].insert(c.second);        
        dsts_by_group[group_of[state[c.second]]].insert(c.first);
        std::swap(state[c.first], state[c.second]);

        // printf("%d, %d: ", c.first, c.second);
        // for (int i = 1; i <= N; i++) {
        //     printf("%d ", state[i]);
        // }
        // printf("\n");
    }
    // printf("\n");

    for (int i = 1; i <= N; i++) {
        // for (int j: dsts_by_group[group_of[i]]) {
        //     printf("%d ", j);
        // }
        printf("%d\n", (int) dsts_by_group[group_of[i]].size());
    }
}