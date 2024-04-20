#include <iostream>
#include <vector>

using namespace std;

#define MAX_N ((int) (3 * 1e4 + 5))
vector<int> graph[MAX_N];
bool vis[MAX_N];

void dfs(int now) {
    if (vis[now]) return;
    vis[now] = true;

    for (int ch: graph[now]) {
        if (!vis[ch]) {
            dfs(ch);
        }
    }

    // I can't come before them, so just let me go right after
    printf("%d ", now);
}

int N, M;
int main(void) {
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        // a owes money to b
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    printf("\n");
}