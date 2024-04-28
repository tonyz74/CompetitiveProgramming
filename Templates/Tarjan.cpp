#include <iostream>
#include <vector>
#include <stack>

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
