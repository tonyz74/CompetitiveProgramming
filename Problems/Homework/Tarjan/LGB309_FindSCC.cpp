#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

#define MAX_N ((int) (2e5 + 7))

int n, m;
vector<int> graph[MAX_N];

int low[MAX_N];
int dfn[MAX_N];
bool vis[MAX_N];
stack<int> stk;

int color_of[MAX_N];

int cnt = 0;
int color = 0;

void tarjan(int x) {
    low[x] = dfn[x] = ++cnt;
    stk.push(x);
    vis[x] = true;

    for (int conn: graph[x]) {
        // not visited yet
        if (dfn[conn] == 0) {
            tarjan(conn);
            low[x] = min(low[x], low[conn]);
        } else {
            // if inside the stack of current candidates for SCC
            if (vis[conn]) {
                low[x] = min(low[x], dfn[conn]);
            }
        }
    }

    if (low[x] == dfn[x]) {
        // everything in the stack up to myself is in my SCC
        int top;
        int new_color = ++color;

        do {
            top = stk.top();
            stk.pop();
            vis[top] = false;
            color_of[top] = new_color;
        } while (top != x);
    }
}

int main(void) {
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            tarjan(i);
        }
    }

    vector<vector<int> > ans(color + 1);
    for (int i = 1; i <= n; i++) {
        ans[color_of[i]].push_back(i);
    }

    std::sort(ans.begin() + 1, ans.end());

    cout << color << endl;
    for (int i = 1; i <= color; i++) {
        for (int j: ans[i]) {
            cout << j << " ";
        }
        cout << endl;
    }
}
